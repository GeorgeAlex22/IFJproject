#include <iostream>
#include <set>
#include <TCut.h>
#include <TString.h>
#include <TDirectory.h>
#include <TEventList.h>
#include "EventMixer.h"

using namespace std; 

EventMixer::EventMixer(TChain& chain, TRandom3& rndGen, const std::string& configFile,
                       const EventCutF eventCutF, const TrackCutF trackCutF):
fConfigMap(configFile),
fChain(chain), fRndGen(rndGen),
fBufferSize(fConfigMap.Get<unsigned int>("bufferSize")),
fMixTimes(fConfigMap.Get<unsigned int>("mixTimes")),
fCBinMin(fConfigMap.Get<unsigned int>("cBinRange",0)),
fCBinMax(fConfigMap.Get<unsigned int>("cBinRange",1)),
fEventCutF(eventCutF), fTrackCutF(trackCutF),
fCurrentRecord(0), fCurrentTag(0), fCurrentTimes(0)
{
        //fChain.SetBranchStatus("*",1); // optionally select branches
        fChain.SetBranchStatus("*",kFALSE);
        fChain.SetBranchStatus("cBin",kTRUE);
        fChain.SetBranchStatus("energySpectatorModules",kTRUE);
        fChain.SetBranchStatus("energyAllPSDModules",kTRUE);
        fChain.SetBranchStatus("tracks.px",kTRUE);
        fChain.SetBranchStatus("tracks.py",kTRUE);
        fChain.SetBranchStatus("tracks.pz",kTRUE);
        fChain.SetBranchStatus("tracks.dEdx",kTRUE);
        fChain.SetBranchStatus("tracks.probElectron",kTRUE);
        fChain.SetBranchStatus("tracks.probPion",kTRUE);
        fChain.SetBranchStatus("tracks.probKaon",kTRUE);
        fChain.SetBranchStatus("tracks.probProton",kTRUE);
        fChain.SetBranchStatus("tracks.probDeuteron",kTRUE);
        fChain.SetBranchStatus("tracks.clustersAll",kTRUE);
        
        fEventTags.reserve(fBufferSize);
        
        /* how many records within cuts? */
        const TCut fCutCBin(Form("cBin >= %d && cBin <= %d", fCBinMin, fCBinMax));
        fChain.Draw(">>eventlist",fCutCBin,"goff");
        TEventList *eventlist = (TEventList*)gDirectory->Get("eventlist");
        fRecordsLeft = eventlist->GetN();
        
        cout << "  Event mixer:  " << endl;
        cout << "----------------" << endl;
        cout << "bufferSize:     " << fBufferSize << endl;
        cout << "mixTimes:       " << fMixTimes << endl;
        cout << "cBinRange:      " << fCBinMin << '\t' << fCBinMax << endl;
        cout << "Total # events: " << fRecordsLeft << endl;
}

void EventMixer::FeedEvent(EventClass::Event *event)
{
    fChain.GetEvent(fCurrentRecord); //read complete accepted event in memory
    
    if ( fEventCutF(*event) &&
        (event->cBin >= fCBinMin) && (event->cBin <= fCBinMax)) {
        
        /* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> BEGIN single track loop >>>>>>>>>>>>>>>>>>>>>>>>>> */
        unsigned int mulTrue = 0;
        for(const auto& t: event->tracks) {// unsigned int nt=0; nt < event->tracks.size(); nt++) {
            if (! fTrackCutF(t) ) continue;   // skip track
            mulTrue++;
            /* add track to fTrackMap */
            fTrackMap[(unsigned int)fTrackMap.size()] = 
                std::make_pair(fCurrentRecord,(EventClass::TrackCore)t);
        }
        /* >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> END   single track loop >>>>>>>>>>>>>>>>>>>>>>>>>> */

        /* push event tag */
        fEventTags.push_back({.eventID = fCurrentRecord,
                              .multiplicity = mulTrue,
                              .cBin = event->cBin,
                              .energySpectatorModules = event->energySpectatorModules,
                              .energyAllPSDModules = event->energyAllPSDModules});        
    }
    fCurrentRecord++;
    return;
}

void EventMixer::FeedCollector()
{
    EventClass::Event *event = new EventClass::Event();
    fChain.SetBranchAddress("Event", &event);

    /* clear fTrackMap, fEventTags */
    fTrackMap.clear();
    fEventTags.clear();
    fCurrentTag = 0;
    fCurrentTimes = 0;
    
    /* Loop over original events */
    unsigned int bakersDozen;
    bool breakEarly;
    if (fRecordsLeft < fBufferSize)
        breakEarly = false;
    else if (fRecordsLeft >= fBufferSize && fRecordsLeft <= 2*fBufferSize-1) {
        breakEarly = true;
        bakersDozen = fRecordsLeft - fBufferSize/2;
    }
    else if (fRecordsLeft >= 2*fBufferSize) {
        breakEarly = true;
        bakersDozen = fBufferSize;
    }
    unsigned int nrecs = fEventTags.size();
    while (fCurrentRecord < fChain.GetEntries()) {
        FeedEvent(event);
        
        if (fEventTags.size() > nrecs) {
            nrecs = fEventTags.size();
            if (nrecs % 10000 == 0) cout<<"Storing event "<< nrecs <<endl;
        }
        
        if (breakEarly)
            if ( fEventTags.size() >= bakersDozen )
                break;
    }
    
    fRecordsLeft -= fEventTags.size();
    return;
}

MaybeEvent EventMixer::randomEvent()
{
    /* have we rolled over to 0-mixing? */
    if (fCurrentTimes == 0 && fCurrentTag == 0)
        if (fRecordsLeft > 0) {
            FeedCollector(); // bring a bunch of events to mix
        } else {             // we're done
            return std::make_pair(false, EventClass::Event() );
        }
    
    EventClass::Event rndEvent;
    /* fill header */
    const unsigned int mul = fEventTags.at(fCurrentTag).multiplicity;
    rndEvent.event_id = fEventTags.at(fCurrentTag).eventID;
    rndEvent.cBin = fEventTags.at(fCurrentTag).cBin;
    rndEvent.energySpectatorModules = fEventTags.at(fCurrentTag).energySpectatorModules;
    rndEvent.energyAllPSDModules = fEventTags.at(fCurrentTag).energyAllPSDModules;
    /* fill tracks */
    set<unsigned int> used_events;
    while (rndEvent.tracks.size() < mul) {
        const unsigned int pos = (unsigned int)fRndGen.Integer(fTrackMap.size());
        auto ret = used_events.emplace( (fTrackMap.at(pos)).first );
        if (ret.second)
            rndEvent.tracks.push_back( EventClass::Track( (fTrackMap.at(pos)).second ) );
    }
    
    /* cycle through event tags */
    fCurrentTag = (fCurrentTag+1 < fEventTags.size())?(fCurrentTag+1):0;

    /* have we rolled over to 0-event? */
    if (fCurrentTag == 0)   // next mixing
        fCurrentTimes = (fCurrentTimes+1 < fMixTimes)?(fCurrentTimes+1):0;
    
    /* return event */
    return std::make_pair(true, rndEvent);
}

    coro_evt::pull_type EventMixer::randomStream(){
        return coro_evt::pull_type(
            [&](coro_evt::push_type& yield){
                while (true) {
                    auto maybe_ev = this->randomEvent();
                    if (! maybe_ev.first) return;
                    yield(maybe_ev.second);
                }
        });
    }
