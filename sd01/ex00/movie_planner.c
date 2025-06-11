#include "movie_planner.h"

struct Plan *create_movie_night_plan(void)
{
    struct Preferences  *prefs = 0;
    struct MovieList    *movies = 0;
    struct Plan         *plan = 0;
    prefs = get_user_preferences();
    if (!prefs)
        return (0);
    movies = find_movies(prefs);
    if (!movies)
        return (free(prefs), NULL);
    plan = build_plan(movies);
    if (!plan)
        return (free(prefs), free(movies), NULL);
    return (plan);
}

// COMPILE WITH gcc -W -W -W -D TEST to test
#ifdef TEST
int main(){};
#endif // TEST