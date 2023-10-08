#include <iostream>

#define RUBRO true
#define NEGRO false

// Estrutura e métodos de árvore Rubro-Negra
template <typename T>
class RubroNegra
{
private:
    // Estrutura de um nó da árvore
    struct Node 
    {
        T chave; 
        Node *pai, *esq, *dir;
        bool cor;
    };

    Node nulo;
    Node *raiz;

    void desalocar (Node *n) 
    {
        if (n != &nulo)
        {
            desalocar(n->esq);
            desalocar(n->dir);
            delete n;
        }
    }

public:
    RubroNegra() : raiz {&nulo} { nulo.cor = NEGRO; }
    ~RubroNegra() { desalocar(raiz); }

    // Funcao auxiliar que faz um acao ao visitar um nó
    // No caso apenas imprime a chave
    void visitar (Node *x) { std::cout << x->chave << "\n";}

    // Percurso em ordem da arvore 
    void emOrdem (Node *x) 
    {
        if (x != &nulo)
        {
            emOrdem(x->esq);
            visitar(x);
            emOrdem(x->dir);
        }
    }

    // Inicia o percurso na arvore pela raiz
    void percorrer() { emOrdem(raiz); }

    // Buscar por chave k na árvore
    Node* buscar(Node *x, T k) 
    {
        if (x == &nulo || x->chave == k) return x;

        if (k < x->chave) return buscar(x->esq, k);
        else              return buscar(x->dir, k);
    }

    Node* busca (T k) { return buscar(raiz, k); }

    // Retorna o menor valor da subárvore enraizada em x
    Node* min(Node *x) 
    {
        if (x->esq == &nulo) return x;
        return min(x->esq);
    }

    // Retorna o maior valor da subárvore enraizada em x
    Node* max(Node *x) 
    {
        if (x->dir == &nulo) return x;
        return max(x->dir);
    }

    // Retorna o valor após x no percurso em-ordem
    Node* sucessor(Node *x) 
    {
        if (x->dir != &nulo) return min(x->dir);

        Node *y = x->pai;
        while (y != &nulo && x == y->dir)
        {
            x = y; 
            y = x->pai;
        }
        return y;
        
    }

    // Retorna o valor anterior a x no percurso em-ordem
    Node* predecessor(Node *x) 
    {
        if (x->esq != &nulo) return max(x->esq);

        Node *y = x->pai;
        while (y != &nulo && x == y->esq)
        {
            x = y;
            y = x->pai;
        }
        return y;
    }

    // Realiza a rotação a direita do nó x
    void rotacaoEsq(Node *x) 
    {
        Node *y = x->dir;
        x->dir = y->esq;

        if (y->esq != &nulo) y->esq->pai = x;

        y->pai = x->pai;

        if (x->pai == &nulo)       raiz = y;
        else if (x == x->pai->esq) x->pai->esq = y;
        else                       x->pai->dir = y;
        
        y->esq = x;
        x->pai = y;
    }

    // Realiza a rotação a esquerda do nó x
    void rotacaoDir(Node *x) 
    {
        Node *y = x->esq;
        x->esq = y->dir;

        if (y->dir != &nulo) y->dir->pai = x;

        y->pai = x->pai;

        if (x->pai == &nulo) raiz = y;
        else if (x == x->pai->esq) x->pai->esq = y;
        else x->pai->dir = y;

        y->dir = x;
        x->pai = y;
    }

    // Preserva as propriedades da árvore RB após inclusão
    void consertarInclusao (Node *z) 
    {
        while (z->pai->cor == RUBRO)
        {
            Node *y;
            if (z->pai == z->pai->pai->esq)
            {
                y = z->pai->pai->dir;

                if (y->cor == RUBRO)
                {
                    z->pai->cor = NEGRO;
                    y->cor = NEGRO;
                    z = y->pai;
                    z->cor = RUBRO;
                }
                else
                {
                    if (z == z->pai->dir)
                    {
                        z = z->pai;
                        rotacaoEsq(z);
                    }
                    z->pai->cor = NEGRO;
                    z->pai->pai->cor = RUBRO;
                    rotacaoDir(z->pai->pai);                    
                }
                
            }
            else
            {
                y = z->pai->pai->esq;

                if (y->cor == RUBRO)
                {
                    z->pai->cor = NEGRO;
                    y->cor = NEGRO;
                    z = y->pai;
                    z->cor = RUBRO;
                }
                else
                {
                    if (z == z->pai->esq)
                    {
                        z = z->pai;
                        rotacaoDir(z);
                    }
                    z->pai->cor = NEGRO;
                    z->pai->pai->cor = RUBRO;
                    rotacaoEsq(z->pai->pai);
                }
            }
        }
        raiz->cor = NEGRO;
    }

    // Insere na árvore o nó z e conserta a árvore depois
    void incluir(Node *z) 
    {
        Node *y = &nulo;
        Node *x = raiz;

        while (x != &nulo)
        {
            y = x;

            if (z->chave < x->chave)
                x = x->esq;
            else
                x = x->dir;
        }
        z->pai = y;

        if (y == &nulo) 
            raiz = z;
        else if (z->chave < y->chave) 
            y->esq = z;
        else 
            y->dir = z;
        
        z->esq = &nulo;
        z->dir = &nulo;
        z->cor = RUBRO;

        consertarInclusao(z);
    }

    // Função auxiliar que cria um nó // e então chama função incluir
    void insercao(T k) {
        Node *z = new Node;
        z->chave = k;

        incluir(z);
    }

    void remover(Node *z);
};

int main() 
{
    // Testando inclusão
    RubroNegra<int> arvore;

    for (int i = 0; i < 20; i++) { arvore.insercao(i); }

    arvore.percorrer();

    return 0;
}