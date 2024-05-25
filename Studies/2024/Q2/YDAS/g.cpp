#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

struct SpeedInfo {
    int l;
    int r;
    int a;
};

struct PrecomputedPoint {
    long long current_time;
    long long current_distance;
    long long current_velocity;
    int acceleration_at_start;
};

std::vector<long long>
find_time_for_distance( const std::vector<PrecomputedPoint>& cumulative_distances,
                        const std::vector<long long>& queries );
auto compute_distances_and_times( const std::vector<SpeedInfo>& speedInfos );
long long compute_remaining_time( const PrecomputedPoint& starting_point, long long d );

auto compute_distances_and_times( const std::vector<SpeedInfo>& speedInfos ) {
    std::vector<PrecomputedPoint> points;
    points.reserve( speedInfos.size() + 1 );

    long long current_distance = 0;
    long long current_time = 0;
    long long current_velocity = 0;

    points.push_back( { current_time, current_distance, current_velocity, speedInfos[0].a } );

    for ( std::size_t i = 0; i < speedInfos.size(); i++ ) {
        const auto [l, r, a] = speedInfos[i];

        long long interval_duration = r - l;
        long long distance = current_velocity * interval_duration;
        if ( a != 0 ) {
            distance += ( a * interval_duration * interval_duration ) / 2;
            current_velocity += a * interval_duration;
        }

        current_distance += distance;
        current_time = r;
        points.push_back( { current_time, current_distance, current_velocity,
                            ( i != speedInfos.size() - 1 ) ? speedInfos[i + 1].a : 0 } );
    }

    return points;
}

std::vector<long long>
find_time_for_distance( const std::vector<PrecomputedPoint>& cumulative_distances,
                        const std::vector<long long>& queries ) {
    std::vector<long long> results;
    results.reserve( queries.size() );
    for ( long long d : queries ) {
        auto it = std::lower_bound( cumulative_distances.begin(), cumulative_distances.end(), d,
                                    []( const PrecomputedPoint& lhs, long long rhs ) {
                                        return lhs.current_distance < rhs;
                                    } );

        if ( it != cumulative_distances.end() && it->current_distance == d ) {
            results.push_back( it->current_time );
            continue;
        }

        if ( it == cumulative_distances.begin() ) {
            results.push_back( 0 );
            continue;
        }

        std::advance( it, -1 );
        results.push_back( it->current_time + compute_remaining_time( *it, d ) );
    }

    return results;
}

long long compute_remaining_time( const PrecomputedPoint& starting_point, long long d ) {
    const auto [_, start_distance, start_velocity, acceleration] = starting_point;
    long long remaining_distance = d - start_distance;

    if ( acceleration == 0 ) {
        return remaining_distance / start_velocity;
    }

    // solving quadratic equation
    // (a * t^2) / 2 + v * t = remaining_distance
    // a * t^2 + 2 * v * t - 2 * remaining_distance = 0
    // t = ( -v + sqrt( v^2 + 2 * a * remaining_distance ) ) / a
    double time = ( -start_velocity
                    + std::sqrt( static_cast<double>( start_velocity * start_velocity )
                                 + 2.0 * acceleration * remaining_distance ) )
                  / acceleration;
    return static_cast<long long>( time );
}

int main() {
    int N;
    std::cin >> N;

    std::vector<SpeedInfo> speedInfos( N );
    for ( int i = 0; i < N; i++ ) {
        std::cin >> speedInfos[i].l >> speedInfos[i].r >> speedInfos[i].a;
    }

    int Q;
    std::cin >> Q;

    std::vector<long long> requests( Q );
    for ( int i = 0; i < Q; i++ ) {
        std::cin >> requests[i];
    }

    auto cumulative_distances = compute_distances_and_times( speedInfos );

    auto results = find_time_for_distance( cumulative_distances, requests );

    for ( long long result : results ) {
        std::cout << result << std::endl;
    }
    return 0;
}
