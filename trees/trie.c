#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* ---------------- Trie ------------------------------------------------ */

typedef struct Trie {
    bool end;                    /* true ⇒ this node marks a root word  */
    struct Trie *child[26];     /* 26 letters of the alphabet           */
} Trie;

static Trie *newNode(void)
{
    Trie *n = calloc(1, sizeof *n);   /* calloc ⇒ child[] = NULL, end = 0 */
    return n;
}

static void trieInsert(Trie *root, const char *word)
{
    Trie *cur = root;
    for (const char *p = word; *p; ++p) {
        int idx = *p - 'a';
        if (!cur->child[idx])
            cur->child[idx] = newNode();
        cur = cur->child[idx];
    }
    cur->end = true;                  /* mark finished root */
}

/* return length of the shortest root that is a prefix of word;
   0 ⇒ no root matches                                                */
static size_t trieMatch(const Trie *root, const char *word)
{
    const Trie *cur = root;
    size_t len = 0;

    for (const char *p = word; *p && *p != ' '; ++p) {
        int idx = *p - 'a';
        if (!cur->child[idx])                /* path breaks → no root */
            return 0;
        cur = cur->child[idx];
        ++len;
        if (cur->end)                        /* shortest root found   */
            return len;
    }
    return 0;
}

/* ---------------- main algorithm ------------------------------------- */

char *replaceWords(char **dictionary, int dictionarySize,
                   const char *sentence)
{
    /* 1. build the trie */
    Trie *root = newNode();
    for (int i = 0; i < dictionarySize; ++i)
        trieInsert(root, dictionary[i]);

    /* 2. prepare an output buffer (same length is safe) */
    size_t n = strlen(sentence);
    char  *out = malloc(n + 1);
    size_t o   = 0;                        /* write index in out[] */

    /* 3. scan the sentence word by word */
    for (size_t i = 0; i < n; ) {

        /* try to match a root for the next word */
        size_t rlen = trieMatch(root, sentence + i);

        if (rlen) {                               /* root exists → copy it */
            memcpy(out + o, sentence + i, rlen);
            o += rlen;

            /* skip the rest of the original word */
            while (i < n && sentence[i] != ' ')
                ++i;
        } else {                                  /* no root → copy word   */
            while (i < n && sentence[i] != ' ')
                out[o++] = sentence[i++];
        }

        /* copy exactly one space (if any) */
        if (i < n && sentence[i] == ' ') {
            out[o++] = ' ';
            ++i;
        }
    }
    out[o] = '\0';
    return out;          /* caller must free() */
}

/* ---------------- minimal test driver -------------------------------- */

#define TEST

#ifdef TEST
int main(void)
{
    char *dict1[] = {"cat","bat","rat"};
    char *s1 = "the cattle was rattled by the battery";
    char *r1 = replaceWords(dict1, 3, s1);
    puts(r1);    /* → "the cat was rat by the bat" */
    free(r1);

    char *dict2[] = {"a","b","c"};
    char *s2 = "aadsfasf absbs bbab cadsfafs";
    char *r2 = replaceWords(dict2, 3, s2);
    puts(r2);    /* → "a a b c" */
    free(r2);

    return 0;
}
#endif