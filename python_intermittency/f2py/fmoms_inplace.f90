module types

    implicit none

    INTEGER, PARAMETER :: INT8  = SELECTED_INT_KIND(2)
    INTEGER, PARAMETER :: INT64 = SELECTED_INT_KIND(15)

end module

subroutine fmoms(points, pairs, nbin,xlow,xupp,&
                                     ylow,yupp,&
                                     xp, np)
    implicit none
    !*************************************************
    !** This function receives a table  of  events, **
    !** xp = (px,py).(np) and sorts them in a grid  **
    !** of (nbin)^2 momentum cells (equally spaced).**
    !** It returns a 2-vector as results:           **
    !** fmul = <n>  and fpair = <n(n-1)>            **
    !*************************************************
    !****************************** Parameters  ***************************************
     double precision, intent(out) :: points, pairs ! Returns {<n> , <n(n-1)>} in M^2
     integer, INTENT(IN)           :: nbin          ! Number of bins M in one dimension
     integer, intent(IN)           :: np            ! number of momenta in xp
     double precision,INTENT(IN)   :: xlow,xupp     ! Lower / upper limit of mom. clusters (X)
     double precision,INTENT(IN)   :: ylow,yupp     ! Lower / upper limit of mom. clusters (Y)
     double precision,INTENT(IN)   :: xp(np,2)      ! Table of momenta (px,py) to be sorted
    !***************************    Local Variables ***********************************
    integer nx, ny, ni, nf, dummy       ! Loop counters
    integer nfull                       ! Number of occupied bins
    double precision :: nbins           ! Total number of bins in 2D
    double precision :: dnbinx,dnbiny   ! nbin/(upp-low) in double precision
    double precision :: norm            ! Normalization factor (1/nbins)
    integer          :: spfreq(np,3)    ! sparse bin frequencies [binx,biny,freq]
!
    nbins = dble(nbin)**2
!
    dnbinx  = dble(nbin)/(xupp-xlow)
    dnbiny  = dble(nbin)/(yupp-ylow)
    norm    = 1.d0 / nbins
    nfull   = 0
    points  = 0.d0
    pairs   = 0.d0
!
    do ni=1,np
        if ( (xp(ni,1)<xlow).or.(xp(ni,1)>=xupp) ) cycle
        if ( (xp(ni,2)<ylow).or.(xp(ni,2)>=yupp) ) cycle
        nx=int((xp(ni,1)-xlow)*dnbinx)+1
        ny=int((xp(ni,2)-ylow)*dnbiny)+1
        
nentry: do dummy = 1,1
            do nf = 1, nfull
                if( (spfreq(nf,1) == nx) .and.  &
                    (spfreq(nf,2) == ny) ) exit nentry
            end do
        
            ! *** new entry ***
            spfreq(nf,1) = nx
            spfreq(nf,2) = ny
            spfreq(nf,3) = 0
            nfull = nf
        end do nentry
        
        points  = points  +      norm
        pairs   = pairs   + 2.d0*norm*dble(spfreq(nf,3))
        spfreq(nf,3) = spfreq(nf,3) + 1
        
    enddo
!
    return
end subroutine fmoms

subroutine vfmoms(points, pairs, nbins,nlats,   &
                  xlow,xupp,ylow,yupp,          &
                  xp, np)
    implicit none
    !****************************** Parameters  ***************************************
     double precision, dimension(nbins,nlats),  &
                     intent(inout) :: points, pairs ! Returns {<n> , <n(n-1)>} in M^2
     integer, intent(in)           :: nbins         ! Number of bins M in one dimension [1:nbins]
     integer, intent(in)           :: nlats         ! Number of lattice positions [1:nlats]
     integer, intent(in)           :: np            ! number of momenta in xp
     double precision, dimension(nlats),        &
                       intent(in)  :: xlow,xupp,&   ! Lower / upper limit of mom. clusters (X)
                                      ylow,yupp     ! Lower / upper limit of mom. clusters (Y)
     double precision,intent(in)   :: xp(np,2)      ! Table of momenta (px,py) to be sorted
    !***************************    Local Variables ***********************************
    integer                        :: nl, nb

    !$OMP PARALLEL DEFAULT(SHARED) PRIVATE(nb,nl)
    !$OMP DO SCHEDULE(DYNAMIC) COLLAPSE(2)
!       ***********************************************
!       ***      And for each lattice...            ***
!       ***********************************************
        do nl = 1, nlats
!           **************************************************
!           **  Momentum space is covered with a 2D grid of **
!           **  (nb)x(nb) cells. The frequency of each cell **
!           ** is calculated. nb is varied, nb: 1 -> nbins  **
!           **************************************************
            do nb = 1, nbins
                call fmoms(points(nb,nl), pairs(nb,nl), nb, &
                                          xlow(nl),xupp(nl),&
                                          ylow(nl),yupp(nl),&
                                          xp, np)
!               ***********************************************
!               *** points = 1/M Sum_{m=1}^M [ nm ]         ***
!               *** pairs  = 1/M Sum_{m=1}^M [ nm*(nm-1) ]  ***
!               ***********************************************
            end do ! nb
        end do ! nl
    !$OMP END  DO NOWAIT
    !$OMP END PARALLEL

end subroutine vfmoms

subroutine vlfmoms(points, pairs, nbin,nlats,   &
                   xlow,xupp,ylow,yupp,         &
                   xp, np)
    implicit none
    !****************************** Parameters  ***************************************
     double precision, dimension(nlats),        &
                     intent(inout) :: points, pairs ! Returns {<n> , <n(n-1)>} in M^2
     integer, intent(in)           :: nbin          ! Number of bins M in one dimension
     integer, intent(in)           :: nlats         ! Number of lattice positions [1:nlats]
     integer, intent(in)           :: np            ! number of momenta in xp
     double precision, dimension(nlats),        &
                       intent(in)  :: xlow,xupp,&   ! Lower / upper limit of mom. clusters (X)
                                      ylow,yupp     ! Lower / upper limit of mom. clusters (Y)
     double precision,intent(in)   :: xp(np,2)      ! Table of momenta (px,py) to be sorted
    !***************************    Local Variables ***********************************
    integer                        :: nl

    !$OMP PARALLEL DEFAULT(SHARED) PRIVATE(nl)
    !$OMP DO SCHEDULE(DYNAMIC)
!       ***********************************************
!       ***          For each lattice...            ***
!       ***********************************************
        do nl = 1, nlats
!           **********************************************
!           **  Momentum space is covered with a 2D     **
!           **  grid of (nbin)x(nbin) cells. The        **
!           **  frequency of each cell is calculated.   **
!           **********************************************
            call fmoms(points(nl), pairs(nl), nbin, &
                         xlow(nl),  xupp(nl),       &
                         ylow(nl),  yupp(nl),       &
                                            xp, np)
!          ***********************************************
!          *** points = 1/M Sum_{m=1}^M [ nm ]         ***
!          *** pairs  = 1/M Sum_{m=1}^M [ nm*(nm-1) ]  ***
!          ***********************************************
        end do ! nl
    !$OMP END  DO NOWAIT
    !$OMP END PARALLEL

end subroutine vlfmoms

subroutine vcummoms(cumpoints,cumpairs, cumweights,    &
                    nsamples, nbins, nlats,            &
                    points,pairs,bweights)
    USE types
    implicit none
    !****************************** Parameters  ***************************************
     double precision, dimension(nsamples,nbins,nlats),     &
                     intent(inout) :: cumpoints, cumpairs   ! Returns cumulative {<n> , <n(n-1)>} in M^2
     integer(INT64),   dimension(nsamples),                 &
                     intent(inout) :: cumweights            ! Returns cumulative weights per sample
     integer, intent(in)           :: nbins                 ! Number of bins M in one dimension [1:nbins]
     integer, intent(in)           :: nlats                 ! Number of lattice positions [1:nlats]
     integer, intent(in)           :: nsamples              ! number of bootstrap samples
     double precision, dimension(nbins,nlats),              &
                       intent(in)  :: points,pairs          ! Returns {<n> , <n(n-1)>} in M^2
     integer(INT8), intent(in)     :: bweights(nsamples)    ! Table of event bootstrap weights per sample
     !***************************    Local Variables ***********************************
     integer                       :: ns, nb, nl
     
     !$OMP PARALLEL WORKSHARE
         FORALL (ns = 1:nsamples,   &
                 nb = 1:nbins,      &
                 nl = 1:nlats)
           cumpoints(ns,nb,nl) = cumpoints(ns,nb,nl) + &
           dble( bweights(ns) ) * points(nb,nl)
           cumpairs(ns,nb,nl)  =  cumpairs(ns,nb,nl) + &
           dble( bweights(ns) ) * pairs(nb,nl)
         END FORALL
         
         FORALL (ns = 1:nsamples)
           cumweights(ns) = cumweights(ns) + int( bweights(ns) ,INT64)
         END FORALL
     !$OMP END PARALLEL WORKSHARE

end subroutine vcummoms

subroutine vindcummoms(cumpoints,cumpairs, cumweights,    &
                       nsamples, nbins, nlats,            &
                       points,pairs,bweights, nbin)
    USE types
    implicit none
    !****************************** Parameters  ***************************************
     double precision, dimension(nsamples,nbins,nlats),     &
                     intent(inout) :: cumpoints, cumpairs   ! Returns cumulative {<n> , <n(n-1)>} in M^2
     integer(INT64),   dimension(nsamples, nbins),          &
                     intent(inout) :: cumweights            ! Returns cumulative weights per sample & bin
     integer, intent(in)           :: nbins                 ! M-bin index in one dimension [1:nbins]
     integer, intent(in)           :: nlats                 ! Number of lattice positions [1:nlats]
     integer, intent(in)           :: nsamples              ! number of bootstrap samples
     double precision, dimension(nlats),                    &
                       intent(in)  :: points,pairs          ! Returns {<n> , <n(n-1)>} in M^2
     integer(INT8), intent(in)     :: bweights(nsamples)    ! Table of event bootstrap weights per sample
     integer, intent(in)           :: nbin                  ! M-bin index to update for this event
     !***************************    Local Variables ***********************************
     integer                       :: ns, nl
     
     !$OMP PARALLEL WORKSHARE
         FORALL (ns = 1:nsamples,   &
                 nl = 1:nlats)
           cumpoints(ns,nbin,nl) = cumpoints(ns,nbin,nl) + &
           dble( bweights(ns) ) * points(nl)
           cumpairs(ns,nbin,nl)  =  cumpairs(ns,nbin,nl) + &
           dble( bweights(ns) ) * pairs(nl)
         END FORALL
         
         FORALL (ns = 1:nsamples)
           cumweights(ns,nbin) = cumweights(ns,nbin) + int( bweights(ns) ,INT64)
         END FORALL
     !$OMP END PARALLEL WORKSHARE

end subroutine vindcummoms
