#include "strategy/mutex_strategy.h"
#include "table/table.h"

int main()
{
    // Example: using MutexStrategy with 5 philosophers
    Table<MutexStrategy<5>> diningTable;
    diningTable.runDinner();

    return 0;
}
