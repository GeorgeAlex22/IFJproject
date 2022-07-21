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
    integer nx, ny, ni                  ! Loop counters
    integer nbins                       ! Total number of bins in 2D
    double precision :: dnbinx,dnbiny   ! nbin/(upp-low) in double precision
    double precision :: norm            ! Normalization factor (1/nbins)
    double precision :: freq(nbin,nbin) ! Table of bin frequencies
!
    nbins = nbin**2
!
    dnbinx = dble(nbin)/(xupp-xlow)
    dnbiny = dble(nbin)/(yupp-ylow)
    norm = 1.d0 / dble(nbins)
    freq    = 0.d0
    points  = 0.d0
    pairs   = 0.d0
!
    do ni=1,np
        if ( (xp(ni,1)<xlow).or.(xp(ni,1)>=xupp) ) cycle
        if ( (xp(ni,2)<ylow).or.(xp(ni,2)>=yupp) ) cycle
        nx=int((xp(ni,1)-xlow)*dnbinx)+1
        ny=int((xp(ni,2)-ylow)*dnbiny)+1

        points  = points  +      norm
        pairs   = pairs   + 2.d0*norm*freq(nx,ny)
        freq(nx,ny)= freq(nx,ny)+ 1.d0
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
                       intent(out) :: points, pairs ! Returns {<n> , <n(n-1)>} in M^2
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
