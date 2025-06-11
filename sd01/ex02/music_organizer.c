#include "music_organizer.h"

struct MusicLibrary *organize_music_library(const char *directory_path)
{
    // controllo validita' della path passata
    if (!directory_path /* || piu' eventualli altri check con un check_directory(directory_path)*/)
        return (NULL);

    struct MusicLibrary *library = 0;
    const char          **filenames = 0;
    struct MusicFile    *buf_mf = 0;

    // creo la libreria e controllo se la creazione e' andata a buon fine
    // se directory_path e' allocata dinamicamente la libero in caso di fallimento
    library = create_music_library();
    if (!library)
        return (/*free(directory_path), */NULL);
    
    filenames = scan_directory(directory_path);
    for (unsigned int i = 0; filenames[i]; i++)
    {
        buf_mf = process_music_file(directory_path, filenames[i]);
        update_music_library(library, buf_mf);
    }

    // se directory_path e' allocata dinamicamente la libero
    // free(directory_path)

    // se process music files crea una copia delle stringhe che gli vengono passate
    // libero le stringhe ed il doppio array filenames, se invece ne preleva il puntatore e basta
    // libero solo il doppio array
    free(filenames);

    return (library);
}