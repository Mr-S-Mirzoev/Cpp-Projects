// H helicopters
// L landing pads
// L >= H

// Sample:
//   X  X X    X
// H      H   H  H H
// Helis: {2, 5, 7, 12}
// Pads:  {0, 7, 11, 14, 16}

// 0 ; max 10^9

0)  Pad, with x=0 [ 2 ]
1)  Pad with x = 7 [ 2 ]
2) Pad with x = 11 [ 4 ]
3) Pad with x = 14 [ 2 ]

// if there is 

[ X - D ; X + D]

// N heli; M pads

bool is_it_possible(std::vector <unsigned> const& helis, std::set <unsigned> pads, unsigned D) { // O(N * log(M))
    for (auto heli : helis) { // O(N)
        auto it = pads.lower_bound(heli - D); // O(log(M))
        if (it == pads.end()) {
            return false;
        }
        
        if (*it < heli + D) {
            return false;
        }
         
        pads.erase(it); // O(log(M))
    }
    
    return true;
}

unsigned safe_max (unsigned A, unsigned B) {
    if (A > B)
        return A - B;
    else
        return B - A;
}

// Use bin search
unsigned minimal_assignment_time(std::vector <unsigned> const& helis, std::vector<unsigned> const& pads) {
    std::set <unsigned> pads_tree(pads);
    
    //   X  X X    X
    //                   H      H   H  H H
    
    //                     X  X X    X
    // H      H   H  H H
    
    // find max and min 
    auto min_it = pads.lower_bound(helis[0]);
    unsigned min = 0;
    if (min_it != pads.end()) {
        if (min_it != pads.begin())
            min = std::min(helis[0] - *(min_it - 1), *min_it - helis[0]);
        else
            min = *min_it - helis[0];
    } else {
        min = helis[0] - *(pads.rbegin());
    }

    auto max = std::max(
        safe_max(*helis.begin(), *pads.rbegin()),
        safe_max(*helis.rbegin(), *pads.begin())
    );

    auto l = min, r = max;
    while (l <= r) {
        unsigned m = (L + R) >> 1;
        bool possible = is_is_possible(helis, pads_tree, r);
        if !possible {
            l = m + 1
        } else {
            r = m − 1
        }
    }
    return r;

    /*
    for (unsigned D = min; D < max; ++D) {
        if (is_is_possible(helis, pads_tree, D) {
            return D;
        }
    }
    */
}