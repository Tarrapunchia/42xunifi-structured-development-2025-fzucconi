#include "playlist_creator.h"

struct Playlist *create_playlist(void)
{
    struct MoodSettings     *mood = NULL;
    struct FilterSettings   *filters = NULL;
    struct SongData         *song = NULL;
    struct Playlist         *playlist = NULL;

    // 1. Analize user's mood
    mood = analyze_user_mood();
    if (!mood)
        return (NULL);

    // 2. Build initial filter settings based on default filters
    filters = default_filters();
    if (!filters)
        return (free_mood_settings(mood), NULL);

    // 3. Refine filters according to mood variations
    struct FilterSettings *new_filters = refine_filters(filters);
    if (!new_filters)
    {
        free_filter_settings(filters);
        free_mood_settings(mood);
        return (NULL);
    }
    // se ritorna lo stesso, vado avanti, se la rifinitura mi ritorna un nuovo set
    // di filtri libero il vecchio set
    if (filters != new_filters)
    {
        struct FilterSettings *buf = new_filters;
        free_filter_settings(filters);
        filters = new_filters;
        new_filters = NULL;
    }

    // 4. Fetch a song depending on filter characteristics
    if (filters_require_popular_song(filters) == NICHE)
        song = fetch_niche_song();
    else
        song = fetch_popular_song();
    if (!song)
    {
        free_filter_settings(filters);
        free_mood_settings(mood);
    }

    // 4. Combine the chosen song into a mood playlist
    playlist = combine_with_mood_playlist(song, mood);

    // se non necessaria nella struct playlist, libero la memoria associata a
    // mood, filters e song, altrimenti, ovviamente, evito
    free_song_data(song);
    free_filter_settings(filters);
    free_mood_settings(mood);

    // ritorna NULL se ha fallito combine_with_mood_playlist o la playlist allocata
    // in caso contrario
    return (playlist);
}