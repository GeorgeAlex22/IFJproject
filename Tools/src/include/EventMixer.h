#ifndef EventMixer_h
#define EventMixer_h

#include <string>
#include <utility>
#include <vector>
#include <functional>
#include <unordered_map>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <boost/coroutine2/all.hpp>
#include <TChain.h>
#include <TRandom3.h>
#include "Event.h"
#include "CutsMap.h"

struct EventTag {
    unsigned int eventID;
    unsigned int multiplicity;
    unsigned int cBin;
    double energySpectatorModules;
    double energyAllPSDModules;
};

typedef std::pair<unsigned int, EventClass::TrackCore> pairET;
typedef std::unordered_map<unsigned int, pairET> TrackMap;
// typedef boost::tuple<unsigned int,unsigned int,double> EventTag;   // multiplicity, cBin, energySpectatorModules
typedef std::vector<EventTag> EventTags;
typedef std::pair<bool, EventClass::Event> MaybeEvent;
typedef boost::coroutines2::coroutine<EventClass::Event> coro_evt;
typedef std::function<bool(const EventClass::TrackCore&)> TrackCutF;
typedef std::function<bool(const EventClass::Event&)> EventCutF;

class EventMixer
{
public:
    EventMixer(TChain& chain, TRandom3& rndGen, const std::string& configFile,
               const EventCutF eventCutF = [](const EventClass::Event& ev){return true;},
               const TrackCutF trackCutF = [](const EventClass::TrackCore& t){return true;});
    MaybeEvent randomEvent();
    coro_evt::pull_type randomStream(); // return random event generator
    
private:
    void FeedEvent(EventClass::Event *event);
    void FeedCollector();
    const CutsMap fConfigMap;
    const unsigned int fBufferSize;
    unsigned int fCurrentRecord;
    unsigned int fRecordsLeft;
    unsigned int fCurrentTag;
    const unsigned int fMixTimes;
    unsigned int fCurrentTimes;
    const unsigned int fCBinMin, fCBinMax;
    EventTags fEventTags;
    TrackMap fTrackMap;
    TChain& fChain;
    TRandom3& fRndGen;
    const EventCutF fEventCutF;
    const TrackCutF fTrackCutF;
};

#endif // #ifndef EventMixer_h
