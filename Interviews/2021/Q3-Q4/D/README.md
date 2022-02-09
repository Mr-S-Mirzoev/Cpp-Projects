# Find the minimal time for helis to land

## Description

    You live in 1D space. You're given coords of helis and landing pads. So H points X1...XH for helis and
    L points for landing pads Y1...YL. L >= H. All points are: 0 < Value < 10^9
    Given that helicopters can fly 1 c.u. / s and the one landing pad can be used by one helicopter. 
    Helis fly simultaniously, find the minimal time to land all of them.

## Input

    H L
    X1 ... XH
    Y1 ... YL

## Output

    Minimal time

## Sample

    X  X X    X
    H      H   H  H H
    .................

    Helis: {2, 5, 7, 12}
    Pads:  {0, 7, 11, 14, 16}

    T_min = 4:
    
    0)  Pad, with x=0 [ 2 ]
    1)  Pad with x = 7 [ 2 ]
    2) Pad with x = 11 [ 4 ]
    3) Pad with x = 14 [ 2 ]
