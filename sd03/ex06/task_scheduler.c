#include "task_scheduler.h"

// SE LA MEMORIA PUNTATA DAI NODI NELLA LISTA TASKS NON VIENE UTILIZZATA DALLE ALTRE
// STRUTTURE (IN PARTICOLAR MODO DA struct ScheduleResult *) E SE TALI NODI SONO ALLOCATI
// DINAMICAMENTE AD OGNI RETURN VA ASSOCIATA LA LIBERAZIONE DELLA MEMORIA STOCCATA NELLA DATA LISTA 

struct ScheduleResult *schedule_tasks(struct TaskList *tasks)
{
    if (!tasks)
        return (NULL);

    struct TaskProfile      *profile;
    struct PriorityMap      *priorities;
    struct ScheduleResult   *result;
    int                     core_count;

    // 1. Profile the provided task list to evaluate load and I/O patterns
    profile = profile_tasks(tasks);
    if (!profile)
        return ;

    // 2. Compute scheduling priorities for each task
    priorities = compute_priorities_mock(profile);
    if (!priorities)
        return (free_task_profile(profile), NULL);

    // 3. Assign tasks to CPU cores using the computed priorities
    core_count = get_available_core_count();
    result = create_schedule_result(core_count);
    if (!result)
    {
        free_priority_map(priorities);
        free_task_profile(profile);
        return (NULL);
    }

    for (int core_id = 0; core_id < core_count; core_id++)
    {
        int task_id = select_best_task(profile);
        if (task_id < 0) break; // non ci sono piu' task da assegnare
        update_schedule_entry(result, core_id, task_id);
    }

    // 4. qualora la memoria puntata da profile e priorities non servisse piu'
    //    all'interno di result, la libero
    free_priority_map(priorities);
    free_task_profile(profile);

    return (result);
}   