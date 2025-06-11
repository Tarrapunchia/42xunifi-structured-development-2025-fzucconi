#include "workout_scheduler.h"

struct WorkoutPlan *create_workout_schedule(char *username)
{
    if (!username)
        return (/*se username allocata dinamicamente free(username),*/NULL);

    struct UserData     *userdata = NULL;
    struct WorkoutPlan  *plan = NULL;
    int                 duration;

    userdata = get_user_data(username);
    if (!userdata)
        return (/*se username allocata dinamicamente free(username),*/NULL);
    
    plan = build_base_plan(userdata);
    if (!plan)
        return (/*se username allocata dinamicamente free(username),*/free_user_data(userdata), NULL);

    struct WorkoutPlan *new_plan = refine_plan(plan, userdata);
    if (!new_plan)
        return (/*se username allocata dinamicamente free(username),*/free_workout_plan(plan), free_user_data(userdata), NULL);
    if (plan != new_plan)
    {
        struct WorkoutPlan *buf = new_plan;
        free_workout_plan(plan);
        plan = new_plan;
        new_plan = NULL;
    }

    duration = determine_duration(plan);
    if (duration <= 0)
        return (/*se username allocata dinamicamente free(username),*/
                free_user_data(userdata), free_workout_plan(plan), NULL);
    
    for (int i = 0; i < duration; i++)
    {
        assign_daily_exercises(plan, i);
        assign_daily_tips(plan, i);
    }

    // se userdata non serve piu', ne libero la memoria con
    free_user_data(userdata);
    // se la memoria puntata e' invece integrata nel workout plan evito
    
    // se char *username allocata dinamicamente allora la libero free(username)

    return (plan);
}