#include <iostream> // Entrada e saida no terminal.
#include <vector> // Vetores de tamanho variavel.
#include <string> // Textos das etapas.
#include <algorithm> // Ordenacao de referencia para testes.
#include <random> // Entradas aleatorias de verificacao.
using namespace std; // Evita repetir std.
struct Contagem { int cmp=0, trocas=0, mov=0; }; // Zera os contadores.
bool mostrar=true; // Controla a impressao das etapas.
void etapa(string acao, const vector<int>& v, Contagem& c) { // Registra o estado atual.
    if(!mostrar) return; // Oculta as etapas nos testes automaticos.
    cout << acao << '\t'; // Mostra a acao.
    for(int x:v) cout << x << ' '; // Mostra o vetor.
    cout << '\t' << c.cmp << '\t' << c.trocas << '\t' << c.mov << '\n'; // Mostra os totais.
} // Fim do registro.
void troca(vector<int>& v, int a, int b, Contagem& c) { // Troca duas posicoes diferentes.
    if(a==b) return; // Nao conta autotroca.
    int aux=v[a]; // Guarda o primeiro valor.
    v[a]=v[b]; // Substitui o primeiro pelo segundo.
    v[b]=aux; // Coloca o valor salvo no segundo lugar.
    c.trocas++; // Conta uma troca real.
} // Fim da troca.
void bubble(vector<int>& v, Contagem& c) { // Bubble sem parada antecipada.
    int n=v.size(); // Guarda o tamanho.
    for(int i=0;i<n-1;i++) { // Faz as passagens.
        for(int j=0;j<n-1-i;j++) { // Percorre a parte ainda nao ordenada.
            c.cmp++; // Conta a comparacao dos vizinhos.
            string acao=to_string(v[j])+" > "+to_string(v[j+1]); // Guarda o par comparado.
            bool maior=v[j]>v[j+1]; // Verifica se precisa trocar.
            if(maior) troca(v,j,j+1,c); // Corrige a ordem do par.
            etapa(acao+(maior?": troca":": mantem"),v,c); // Registra o resultado.
        } // Fim da passagem interna.
    } // Fim das passagens.
} // Fim do Bubble.
void selection(vector<int>& v, Contagem& c) { // Seleciona o menor da parte restante.
    int n=v.size(); // Guarda o tamanho.
    for(int i=0;i<n-1;i++) { // Escolhe a posicao a preencher.
        int menor=i; // Assume o primeiro como minimo.
        for(int j=i+1;j<n;j++) { // Procura no restante.
            c.cmp++; // Conta a comparacao de valores.
            string acao=to_string(v[j])+" < "+to_string(v[menor]); // Guarda a comparacao.
            bool achou=v[j]<v[menor]; // Verifica se encontrou um novo minimo.
            if(achou) menor=j; // Atualiza o indice do minimo.
            etapa(acao+(achou?": novo minimo":": mantem minimo"),v,c); // Mostra a busca.
        } // Fim da busca.
        troca(v,i,menor,c); // Coloca o menor no inicio do trecho.
        etapa("Posiciona minimo: i="+to_string(i)+", menor="+to_string(menor),v,c); // Mostra a colocacao.
    } // Fim das escolhas.
} // Fim do Selection.
void insertion(vector<int>& v, Contagem& c) { // Insere valores na parte ordenada.
    int n=v.size(); // Guarda o tamanho.
    for(int i=1;i<n;i++) { // Comeca pelo segundo valor.
        int chave=v[i], j=i-1; // Guarda a chave e o indice anterior.
        etapa("Chave="+to_string(chave),v,c); // Identifica a rodada.
        while(j>=0) { // Procura a posicao da chave.
            c.cmp++; // Conta apenas a comparacao entre valores.
            bool maior=v[j]>chave; // Verifica se o valor deve andar.
            etapa(to_string(v[j])+" > chave "+to_string(chave)+(maior?": sim":": nao"),v,c); // Mostra a comparacao.
            if(!maior) break; // Para quando encontra o lugar certo.
            v[j+1]=v[j]; // Desloca o valor para a direita.
            c.mov++; // Conta deslocamento, sem chamar de troca.
            etapa("Desloca para indice "+to_string(j+1),v,c); // Mostra o vetor parcial.
            j--; // Continua pela esquerda.
        } // Fim da busca.
        v[j+1]=chave; // Insere a chave no lugar encontrado.
        etapa("Insere chave no indice "+to_string(j+1),v,c); // Mostra a insercao.
    } // Fim das insercoes.
} // Fim do Insertion.
void intercalar(vector<int>& v,int ini,int meio,int fim,Contagem& c) { // Junta duas metades ordenadas.
    vector<int> a(v.begin()+ini,v.begin()+meio+1); // Copia a metade esquerda.
    vector<int> b(v.begin()+meio+1,v.begin()+fim+1); // Copia a metade direita.
    int i=0,j=0,k=ini; // Inicia os indices das copias e do destino.
    etapa("Intercala ["+to_string(ini)+","+to_string(meio)+"] e ["+to_string(meio+1)+","+to_string(fim)+"]",v,c); // Identifica os trechos.
    while(i<(int)a.size() && j<(int)b.size()) { // Continua enquanto as duas partes tem valores.
        c.cmp++; // Conta a comparacao das frentes.
        string acao=to_string(a[i])+" <= "+to_string(b[j]); // Guarda os valores comparados.
        if(a[i]<=b[j]) v[k++]=a[i++]; // Copia o menor da esquerda.
        else v[k++]=b[j++]; // Copia o menor da direita.
        c.mov++; // Conta uma escrita no vetor original.
        etapa(acao+": copia menor",v,c); // Mostra a escrita.
    } // Fim das comparacoes da intercalacao.
    while(i<(int)a.size()) { // Copia o restante da esquerda.
        v[k++]=a[i++]; // Escreve o valor restante.
        c.mov++; // Conta a escrita.
        etapa("Copia restante esquerdo",v,c); // Mostra a copia sem comparar valores.
    } // Fim do restante esquerdo.
    while(j<(int)b.size()) { // Copia o restante da direita.
        v[k++]=b[j++]; // Escreve o valor restante.
        c.mov++; // Conta a escrita.
        etapa("Copia restante direito",v,c); // Mostra a copia sem comparar valores.
    } // Fim do restante direito.
} // Fim da intercalacao.
void merge(vector<int>& v,int ini,int fim,Contagem& c) { // Divide e intercala recursivamente.
    if(ini>=fim) return; // Para em trecho vazio ou unitario.
    int meio=ini+(fim-ini)/2; // Calcula o meio.
    etapa("Divide ["+to_string(ini)+","+to_string(fim)+"] no meio "+to_string(meio),v,c); // Mostra a divisao.
    merge(v,ini,meio,c); // Ordena a esquerda.
    merge(v,meio+1,fim,c); // Ordena a direita.
    intercalar(v,ini,meio,fim,c); // Junta as partes.
} // Fim do Merge.
int particao(vector<int>& v,int ini,int fim,Contagem& c) { // Usa a particao de Lomuto.
    int pivo=v[fim],i=ini-1; // Escolhe o ultimo valor como pivo.
    etapa("Particao ["+to_string(ini)+","+to_string(fim)+"]; pivo="+to_string(pivo),v,c); // Identifica o trecho.
    for(int j=ini;j<fim;j++) { // Percorre os valores antes do pivo.
        c.cmp++; // Conta uma comparacao com o pivo.
        string acao=to_string(v[j])+" <= pivo "+to_string(pivo); // Guarda os valores comparados.
        bool menor=v[j]<=pivo; // Decide em qual lado o valor fica.
        if(menor) { // Aumenta a parte menor ou igual.
            i++; // Avanca a fronteira esquerda.
            troca(v,i,j,c); // Coloca o valor no lado esquerdo.
        } // Fim do tratamento do valor menor.
        etapa(acao+(menor?": esquerda":": mantem"),v,c); // Mostra a comparacao e eventual troca.
    } // Fim da passagem.
    troca(v,i+1,fim,c); // Coloca o pivo na posicao definitiva.
    etapa("Pivo no indice "+to_string(i+1),v,c); // Mostra a posicao final.
    return i+1; // Retorna a posicao do pivo.
} // Fim da particao.
void quick(vector<int>& v,int ini,int fim,Contagem& c) { // Ordena os lados do pivo.
    if(ini>=fim) return; // Para em trechos com menos de dois valores.
    int p=particao(v,ini,fim,c); // Divide pelo pivo.
    quick(v,ini,p-1,c); // Ordena a esquerda.
    quick(v,p+1,fim,c); // Ordena a direita.
} // Fim do Quick.
void ordenar(int tipo,vector<int>& v,Contagem& c) { // Seleciona um dos cinco algoritmos.
    if(tipo==0) bubble(v,c); // Chama Bubble.
    else if(tipo==1) selection(v,c); // Chama Selection.
    else if(tipo==2) insertion(v,c); // Chama Insertion.
    else if(tipo==3) merge(v,0,(int)v.size()-1,c); // Chama Merge.
    else quick(v,0,(int)v.size()-1,c); // Chama Quick.
} // Fim da selecao.
int main(int argc,char* argv[]) { // Inicia o programa.
    if(argc>1 && string(argv[1])=="--test") { // Ativa a verificacao automatica.
        mostrar=false; // Desliga os registros detalhados.
        mt19937 rng(2026); // Define uma semente repetivel.
        for(int t=0;t<1000;t++) { // Gera mil entradas.
            vector<int> entrada(t%21); // Inclui tamanhos de zero a vinte.
            for(int& x:entrada) x=(int)(rng()%21)-10; // Inclui negativos e repetidos.
            vector<int> esperado=entrada; // Copia a entrada para a referencia.
            sort(esperado.begin(),esperado.end()); // Calcula a resposta esperada.
            for(int tipo=0;tipo<5;tipo++) { // Testa cada algoritmo.
                vector<int> v=entrada; // Usa uma copia nova.
                Contagem c; // Zera os contadores.
                ordenar(tipo,v,c); // Executa a ordenacao.
                if(v!=esperado) return 1; // Interrompe em caso de erro.
            } // Fim dos cinco algoritmos.
        } // Fim das mil entradas.
        cout << "5000 verificacoes passaram.\n"; // Informa o sucesso.
        return 0; // Encerra o modo de teste.
    } // Fim da verificacao automatica.
    vector<int> entrada={5,3,4,1,2}; // Entrada comum dos testes de mesa.
    string nomes[]={"Bubble sort","Selection sort","Insertion sort","Merge sort","Quick sort"}; // Nomes dos algoritmos.
    for(int tipo=0;tipo<5;tipo++) { // Executa as cinco versoes.
        vector<int> v=entrada; // Restaura a entrada original.
        Contagem c; // Zera os contadores.
        cout << "ALGORITMO\t" << nomes[tipo] << '\n'; // Identifica a tabela.
        etapa("Entrada",v,c); // Registra o inicio.
        ordenar(tipo,v,c); // Executa o algoritmo.
        etapa("Resultado",v,c); // Registra o resultado e os totais.
    } // Fim das execucoes.
    return 0; // Encerra normalmente.
} // Fim do programa.
