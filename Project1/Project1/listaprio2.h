typedef struct _listaprio ListaP;

/* cria nova lista de prioridades, opcionalmente passando uma lista inicial de prios */
ListaP *listap_cria (int max);

/* insere uma nova prioridade na lista */
void listap_insere (ListaP *lp, int prioridade, int dado); 

/* remove e retorna a menor prioridade */
int listap_remove (ListaP *lp);

/* libera a lista de prioridades */
void listap_libera (ListaP *lp);

/* corrige a prioridade associada a determinado valor */
void listap_corrige (ListaP* heap, int novaprio, int dado);

/* só para debug: enxerga representação interna! */
void debug_listap_show (ListaP *hp, char* title);

