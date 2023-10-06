
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

    Node* sucessor(Node *x);
    Node* predecessor(Node *x);

    void incluir(Node *z);
    void remover(Node *z);

};

int main() 
{
    return 0;
}