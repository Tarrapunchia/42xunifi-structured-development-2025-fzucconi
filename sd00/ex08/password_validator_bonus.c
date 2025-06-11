#include "password_validator.h"

int min(int x, int y, int z)
{
    if (x < y && x < z)
        return x;
    else if (y < x && y < z)
        return y;
    else
        return z;
}

// Calcola il numero minimo di operazioni necessarie per trasformare new_pw in
// old_pw (uso distanza di Levenshtein)
// 3 operazioni possibili:
//  - inserimento di un carattere
//  - cancellazione o rimozione di un carattere
//  - sostituzione di un carattere
int minDis(const char* new_pw, const char* old_pw, int n, int m)
{
    // array dinamico per memoizzazione
    int d_array[n + 1][m + 1];

    // calcolo la minima edit distance d_array[i][j] tra new_pw[0..i-1] e old_pw[0..j-1]
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
            // se new_pw e' vuota allora la distanza e' j (inserisco tutti i char di old_pw)
            if (i == 0)
                d_array[i][j] = j;
            // se old_pw e' vuota allora devo rimuovere tt i char di new_pw (distanza i)
            else if (j == 0)
                d_array[i][j] = i;
            // Se gli ultimi carattere coincidono li ignoro e vado a controllare gli altri
            // e cosi via (eredito il costo del sottoproblema, via)
            else if (new_pw[i - 1] == old_pw[j - 1])
                d_array[i][j] = d_array[i - 1][j - 1];
            // Se non coincidono considero le 3 possibili azioni:
            //  - inserimento di old_pw[j-1] in new_pw[0..i-1]: dopo inserimento (1) devo ancora trasformare
            //    new_pw[0..i-1] in old_pw[0..j-2] al costo di d_array[i][j-1] + 1 totale
            //  - cancellazione di new_pw[i-1]: dopo la cancellazione, devo ancora trasformare 
            //    new_pw[0..i-2] in old_pw[0..j-1] al costo d_array[i-1][j] + 1
            //  - sostituzione new_pw[i-1] con old_pw[j-1]: dopo la sostituzione,
            //    trasformo new_pw[0..i-2] in old_pw[0..j-2] al costo d_array[i-1][j-1] + 1
            // PRENDO IL MINIMO DEI 3 E LO ASSEGNO A d_array[i][j]
            // cosi posso scorrere tutte e due le stringhe e computare sommando le distanze minime
            // per la trasformazione dell'una nell'altra
            else
                d_array[i][j] = 1
                           + min(d_array[i][j - 1], d_array[i - 1][j],
                                 d_array[i - 1][j - 1]);
        }
    }
    // Ritorno la distanza
    return d_array[n][m];
}

int	ft_strlen(const char *s)
{
	int	i;

	if (s == 0)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

PwStatus validate_password(const char *new_pw, PasswordHistory *head)
{
    PwStatus status = 0x00;
    if (!new_pw || !head || !head)
        return (FAILURE);
    status = validate(new_pw, (const char*)head->pw);
    if (status == INVALID_WEAK)
        return (status);
    int len1 = ft_strlen(new_pw);
    PasswordHistory *buf = head;
    for (int i = 0; buf && i < 3; i++)
    {
        int len2 = 0;
        len2 = ft_strlen((const char*)buf->pw);
        if (minDis(new_pw, (const char*)buf->pw, len1, len2) < 2)
            status = INVALID_SIMILAR;
        buf = buf->next;
    }

    return (status);
}

// TO TEST COMPILE WITH gcc -W -W -W -D TEST
#ifdef TEST

PasswordHistory *add_pw_to_history(PasswordHistory *head, const char *pw)
{
    if (!pw)
        return head;
    if (!head)
    {
        head = malloc(sizeof(PasswordHistory));
        if (!head)
            return head;
        head->pw = malloc(ft_strlen(pw));
        strncpy(head->pw, pw, ft_strlen(pw));
        head->next = 0;
        return head;
    }
    else
    {
        PasswordHistory *buf = 0;
        buf = malloc(sizeof(PasswordHistory));
        if (!buf)
            return head;
        buf->pw = malloc(ft_strlen(pw)); 
        strncpy(buf->pw, pw, ft_strlen(pw));
        buf->next = head;
        return buf;
    }
}

int main()
{
    char *old[] = {"Ciao123@", "NONNAa1@@", "Canide23@", 0};
    PasswordHistory *head = 0;
    head = add_pw_to_history(head, "Ciao123@");
    head = add_pw_to_history(head, "NONNAa1@@");
    head = add_pw_to_history(head, "Canide23@");
    const char new[] = "Ciao124@";
    printf("Old pw: %s, new pw: %s\nvalid? %d\n", *old, new, validate_password(new, head));
}
#endif // TEST
