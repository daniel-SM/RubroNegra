#define NEGRO false;
#define RUBRO true;

template <typename T>
class RubroNegra
{
private:
    struct Node 
    {
        Node *pai, *esq, *dir;
        T chave; 
        bool cor;
    };

    Node *raiz;
    Node nulo;

public:
    RubroNegra() : raiz {&nulo} {}

    Node* buscar(Node *x, T k) 
    {
        if (x == &nulo || x->chave == k) return x;

        if (k < x->chave) return buscar(x->esq, k);
        else              return buscar(x->dir, k);
    }

    Node* min(Node *x) 
    {
        if (x->esq == &nulo) return x;
        return min(x->esq);
    }

    Node* max(Node *x) 
    {
        if (x->dir == &nulo) return x;
        return max(x->dir);
    }

    Node* sucessor(Node *x) 
    {
        if (x->dir != &nulo) return min(x->dir);

        y = x->pai;
        while (y != &nulo && x == y->dir)
        {
            x = y; 
            y = x->pai;
        }
        return y;
        
    }

    Node* predecessor(Node *x) 
    {
        if (x->esq != &nulo) return max(x->esq);

        y = x->pai;
        while (y != &nulo && x == y->esq)
        {
            x = y;
            y = x->pai;
        }
        return y;identifier
    }

    void RotEsq(Node *x) 
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

    void RotDir(Node *x) 
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

    void consertarInclusao (Node *z) 
    {
        while (z->pai->cor == RUBRO)
        {
            Node *y;
            if (z->pai == z->pai->pai>esq)
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
                        RotEsq(z);
                    }
                    z->pai->cor = NEGRO;
                    z->pai->pai->cor = RUBRO;
                    RotDir(z->pai->pai);                    
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
                        RotDir(z);
                    }
                    z->pai->cor = NEGRO;
                    z->pai->pai->cor = RUBRO;
                    RotEsq(z->pai->pai);
                }
            }
        }
        raiz->cor = NEGRO;
    }

    void incluir(Node *z) 
    {

    }

    void remover(Node *z);

};

int main() 
{
    return 0;
}