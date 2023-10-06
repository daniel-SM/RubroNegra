
template <typename T>
class RubroNegra
{
private:
    struct Node 
    {
        Node *pai, *esq, *dir;
        T chave;
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
        return y;
    }

    void incluir(Node *z);
    void remover(Node *z);

};

int main() 
{
    return 0;
}