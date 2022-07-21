module types

    implicit none

    INTEGER, PARAMETER :: INT8  = SELECTED_INT_KIND(2)
    INTEGER, PARAMETER :: INT64 = SELECTED_INT_KIND(15)

end module

module cordim

    contains

    FUNCTION locate(n,xx,x)
    IMPLICIT NONE
    integer, intent(IN) :: n
    double precision, DIMENSION(n), INTENT(IN) :: xx
    double precision, INTENT(IN) :: x
    integer :: locate
    !*****************************************************
    !*** Given an array xx(1:N ), and given a value x, ***
    !*** returns a value j such that x is between      ***
    !*** xx(j ) and xx(j + 1). xx must be monotonic,   ***
    !*** either increasing or decreasing. j = 0 or     ***
    !*** j = N is returned to indicate that x is out   ***
    !*** of range.                                     ***
    !*****************************************************
    INTEGER :: jl,jm,ju
    LOGICAL :: ascnd
    ascnd = (xx(n) >= xx(1))       ! True if ascending order of table, false otherwise.
    jl=0                           ! Initialize lower
    ju=n+1                         ! and upper limits.
    do
        if (ju-jl <= 1) exit       ! Repeat until this condition is satisﬁed.
        jm=(ju+jl)/2               ! Compute a midpoint,
        if (ascnd .eqv. (x >= xx(jm))) then
            jl=jm                  ! and replace either the lower limit
        else
            ju=jm                  ! or the upper limit, as appropriate.
        end if
    end do
    if (x == xx(1)) then           ! Then set the output, being careful with the endpoints.
        locate=1
    else if (x == xx(n)) then
        locate=n-1
    else
        locate=jl
    end if
    END FUNCTION locate



subroutine pairs(npairs, nstops,    &
                 thresR2,           &
                 xp, np)
    USE types
    implicit none
    !****************************** Parameters  ***************************************
    integer(INT64), dimension(nstops+1), &          ! Holds #pairs with distance <=i-th
                     intent(INOUT) :: npairs        ! stop R_i, 1 <= i <= N
                                                    ! N+1 -> overflow (distance > N-th stop)
    integer,         intent(IN)    :: nstops        ! Number of pair distance stops to be tabulated
    double precision, DIMENSION(nstops), &
                     intent(IN)    :: thresR2       ! R**2 stops to calculate #pairs before;
    integer,         intent(IN)    :: np            ! number of momenta in xp
    double precision,intent(IN)    :: xp(np,2)      ! Table of momenta (px,py) to be sorted
    !***************************    Local Variables ***********************************
    integer                        :: fst, snd, nd, idx
    double precision               :: dist2

!   *******************************************
!   ***      initialize #pairs array        ***
!   *******************************************
    npairs = 0

!   *******************************************
!   ***        loop through pairs           ***
!   *******************************************
    do snd = 2, np
        do fst = 1, snd-1
!           ***********************************
!           ***  calculate pair distance^2  ***
!           ***********************************
            dist2 = 0.d0
            do nd = 1,2
                dist2 = dist2 + ( xp(snd,nd) - xp(fst,nd) )**2
            end do ! nd
!           ***********************************
!           ***     calculate bin number    ***
!           ***********************************
            idx = locate(nstops, thresR2, dist2) + 1
!           ***********************************
!           ***     increment bin counts    ***
!           ***********************************
            npairs(idx:) = &
            npairs(idx:) + 1_INT64
        end do ! fst
    end do ! snd

end subroutine pairs

subroutine cumpairs(cumnpairs, cumweights,  &
                     nsamples, nstops,      &
                       npairs,   bweights)
    USE types
    implicit none
    !****************************** Parameters  ***************************************
     integer(INT64), dimension(nsamples,nstops+1),  &
                     intent(INOUT) :: cumnpairs             ! Holds cumulative #pairs
     integer(INT64), dimension(nsamples),           &
                     intent(INOUT) :: cumweights            ! Returns cumulative weights per sample
     integer,        intent(IN)    :: nsamples              ! number of bootstrap samples
     integer,        intent(IN)    :: nstops                ! Number of pair distance stops to be tabulated
     integer(INT64), dimension(nstops+1),           &       ! Holds #pairs with distance <=i-th
                     intent(IN)    :: npairs                ! stop R_i, 1 <= i <= N
                                                            ! N+1 -> overflow (distance > N-th stop)
     integer(INT8),  intent(IN)    :: bweights(nsamples)    ! Table of event bootstrap weights per sample
     !***************************    Local Variables ***********************************
     integer                       :: ns, nR
     
     !$OMP PARALLEL WORKSHARE
         FORALL (ns = 1:nsamples,   &
                 nR = 1:(nstops+1))
           cumnpairs(ns,nR) = cumnpairs(ns,nR) + int( bweights(ns) ,INT64) * npairs(nR)
         END FORALL
         
         FORALL (ns = 1:nsamples)
           cumweights(ns) = cumweights(ns) + int( bweights(ns) ,INT64)
         END FORALL
     !$OMP END PARALLEL WORKSHARE

end subroutine cumpairs

end module cordim
