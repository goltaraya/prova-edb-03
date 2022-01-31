#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

// Aluno: Yago Alexandre Goltara Affonso - Eng. Comput. - 2020.2
// Matr�cula: -----------
// Disc.: Estrutura de Dados B�sicos

// Prova 03

// Declara��o das Structs
typedef struct arvProduto{				// �rvore dos Produtos
	int codigo; 				// informa��o escolhida para ordena��o
	int unidades;
	float valor;
	char nome[30];
	char descricao[50];
	
	int altura;				// altura do n�
	struct arvProduto *esq;
	struct arvProduto *dir;
}ArvProd;

typedef struct arvCliente{			// �rvore dos Clientes
	int codigo;					// informa��o escolhida para ordena��o
	char cpf[12];
	char nome[30];
	
	int altura;					// altura do n�
	struct arvCliente *esq;
	struct arvCliente *dir;
}ArvCliente;

typedef struct arvVendas{			// �rvore das Vendas
	int codigo_venda;	// informa��o escolhida para ordena��o
	int codigo_produto;
	float valor;
	char cpf[12];
	char nome_comprador[30];
	
	int altura;				// altura do n�
	struct arvVendas *esq;
	struct arvVendas *dir;
}ArvVenda;

/* Declara��o de fun��es -----------------------------------------------------> */
// Fun��es auxiliares
void stop();			// Fun��o para parar e limpar a tela
ArvProd *rotacaoR(ArvProd *a);		// Fun��o de rota��o para Direita (Right)
ArvProd *rotacaoL(ArvProd *a);		// Fun��o de rota��o para Esquerda (Left)
int maximo(int x, int y);					// Calcula o valor m�x de qual dos lados
int alturaArvProd(ArvProd *a);		// Calcula a altura da �rvore de Produtos
int alturaArvCliente(ArvCliente *a); // Calcula a altura da �rvore de Clientes
ArvCliente *rotacaoLC(ArvCliente *a);	// Rota��o para Esquerda aplicada na �rvore de Clientes
ArvCliente *rotacaoRC(ArvCliente *a); // Rota��o para Direita aplicada na �rvore de Clientes
int fatorBalanceador(ArvProd *a);	// Calcula o balanceamento aplicada na �rvore de Produtos

// Fun��es referentes aos produtos			
ArvProd *criarArvProd();					// Inicializa a �rvore de Produtos
int estaVaziaArvProd(ArvProd *a); // Verifica se a �rvore de Produtos est� vazia
ArvProd *novoProduto(int codigo);	// Cria um novo produto
ArvProd *inserirProd(ArvProd *a, int codigo); // Insere o produto criado na fun��o anterior na �rvore de Produtos
int buscarProd(ArvProd *a, int codigo_produto);	// Busca um produto a partir de seu c�digo e retorna 0 se n�o achado e 1 se achado
void exibirEstoqueInOrdem(ArvProd *a);	// Imprime o estoque de Produtos em In-Ordem

// Fun��es referentes aos clientes			
ArvCliente *criarArvCliente();					// Inicializa a �rvore de Clientes
int estaVaziaArvCliente(ArvCliente *a);	// Verifica se a �rvore de Clientes est� vazia
ArvCliente *novoCliente(int codigo);		// Cria um novo cliente
ArvCliente *inserirCliente(ArvCliente *a, int codigo);		// Insere o cliente criado na fun��o anterior na �rvore de Clientes
int buscarCliente(ArvCliente *a, int codigo_cliente);			// Busca um cliente a partir de seu c�digo
ArvCliente *removerCliente(ArvCliente *a, int codigo_cliente);	 // Remove um cliente da �rvore de Clientes
ArvCliente *menor(ArvCliente *a);				// Acha o menor n� da �rvore de Clientes
void exibirClienteInOrdem(ArvCliente *a);	// Imprime a �rvore de Clientes In-Ordem

// Fun��es referentes �s vendas
ArvVenda *criarArvVenda();						// Inicializa a �rvore de Vendas
int estaVaziaArvVenda(ArvVenda *a);		// Verifica se a �rvore de Vendas est� vazia
ArvVenda *criarVenda(int codigo, ArvCliente *c, ArvProd *p);					// Cria uma nova venda
ArvVenda *realizarVenda(ArvVenda *a, int codigo, ArvCliente *c, ArvProd *p);	// Insere a venda criada dentro da �rvore de Vendas
void imprimirVendas(ArvVenda *a);						// Imprime as vendas realizadas em In-Ordem
int vendasTotais(ArvVenda *a);							// Calcula a quantidade de vendas feitas (a partir da contagem de n�s da �rvore de Vendas)
ArvVenda *rotacaoLV(ArvVenda *a);						// Rota��o a Esquerda na �rvore de Vendas
ArvVenda *rotacaoRV(ArvVenda *a);						// Rota��o a Direita na �rvore de Vendas
int alturaArvVenda(ArvVenda *a);						// Calcula altura na �rvore de Vendas
int fatorBalanceadorV(ArvVenda *a);					// Calcula balanceamento da �rvore de Vendas
ArvProd *buscarProdParaVenda(ArvProd *a, int codigo);						// Busca um produto e manipula nas vendas
ArvCliente* buscarClienteParaVenda(ArvCliente *a, int codigo);	// Busca um cliente e manipula nas vendas

// (------------ Fun��o principal ------------)
void main(){
	system("COLOR E1");
	setlocale(LC_ALL, "portuguese");
	
	// Declara��o de vari�veis 
	ArvProd *produto;
	ArvCliente *cliente;
	ArvVenda *venda;
	int opcao;
	int codigo_produto, codigo_cliente, codigo_venda;
	int buscaproduto, buscacliente, buscavenda;
	int deseja_sair = 0;	// flag para inicializar o while-loop
	
	// Cria��o das �rvores
	produto = criarArvProd();
	cliente = criarArvCliente();
	venda = criarArvVenda();
	
	// In�cio do loop para o MENU PRINCIPAL
while(deseja_sair != 1){
	printf("\t|PETSHOP PET FELIZ|\n\n");
	printf("< 1 >\tCadastrar produto\n< 2 >\tBuscar produto\n< 3 >\tExibir estoque\n< 4 >\tCadastrar cliente\n");
	printf("< 5 >\tExcluir cliente\n< 6 >\tBuscar cliente\n< 7 >\tClientes cadastrados\n< 8 >\tRealizar venda\n< 9 >\tConsultar vendas\n");
	printf("< 10 >\tExibir quantidade de vendas\n< 11 >\tSair");
	printf("\nInsira um comando >>> ");
	scanf("%d", &opcao);
	system("cls");
	
	switch(opcao){
		case 1:
			printf("\t|CADASTRAR PRODUTO|\n");
			printf("Ol�, para cadastrar um produto primeiramente insira um c�digo de sua escolha para identific�-lo: ");
			scanf("%d", &codigo_produto);
			produto = inserirProd(produto, codigo_produto);
			printf("Produto cadastrado com sucesso!\n");
			stop();
		break;		
		
		case 2:
			printf("\t|BUSCAR PRODUTO|\n");
			if(estaVaziaArvProd(produto) == 1){
				printf("Desculpe... o estoque se encontra vazio no momento.\nPor favor, retorne � tela inicial e insira um novo produto.\n");
			} else {	
			printf("Para buscar um produto, insira seu c�digo no campo abaixo:\n");
			scanf("%d", &codigo_produto);
			buscaproduto = buscarProd(produto, codigo_produto);
			if(buscaproduto != 0){
				printf("Produto encontrado!\n");
			} else {
				printf("Produto n�o encontrado.\n");
			}
			}
			stop();
		break;
	
	case 3:
	printf("\t|ESTOQUE|\n");
	if(estaVaziaArvProd(produto) == 1){
		printf("Desculpe... o estoque se encontra vazio no momento.\nPor favor, retorne � tela inicial e insira um novo produto.\n");
	} else {
		exibirEstoqueInOrdem(produto);
	}
	stop();
	break;
	
	case 4:
		printf("\t|CADASTRAR CLIENTE|\n");
		printf("Para cadastrar um novo cliente, primeiro insira um c�digo de sua escolha para\nidentica��o do mesmo: ");
		scanf("%d", &codigo_cliente);
		cliente = inserirCliente(cliente, codigo_cliente);
		printf("Cliente cadastrado com sucesso!\n");
		stop();
	break;
	
	case 5:
		printf("\t|REMOVER CLIENTE|\n");
		if(estaVaziaArvCliente(cliente) == 1){
			printf("Desculpe... a lista de clientes se encontra vazia no momento.\nPor favor, retorne � tela inicial e cadastre um novo cliente.\n");
		} else {
			printf("Primeiramente, insira o c�digo de identifica��o do cliente: ");
			scanf("%d", &codigo_cliente);
			buscacliente = buscarCliente(cliente, codigo_cliente);
			if(buscacliente == 0){
				printf("Cliente n�o encontrado. Retorne ao menu principal.\n");
			} else {
				cliente =	removerCliente(cliente, codigo_cliente);
				printf("Cliente exclu�do do sistema com sucesso!\n");
			}
		}
		stop();
	break;
	
	case 6:
		printf("\t|BUSCAR CLIENTE|\n");
		if (estaVaziaArvCliente(cliente) == 1){
			printf("Desculpe... a lista de clientes se encontra vazia no momento.\nPor favor, retorne � tela inicial e cadastre um novo cliente.\n");
		} else {
		printf("Insira o c�digo do cliente que deseja buscar: ");
		scanf("%d", &codigo_cliente);
		buscacliente = buscarCliente(cliente, codigo_cliente);
		if(buscacliente == 1){
			printf("Cliente encontrado.\n");
		} else {
			printf("Cliente n�o encontrado.\n");
		}
		}
		stop();
	break;
	
	case 7:
		printf("\t|CLIENTES CADASTRADOS|\n");
		if(estaVaziaArvCliente(cliente) == 1){
			printf("Ops... a lista de clientes n�o existe. Retorne ao menu principal e cadastre-os.\n");
		} else {
			exibirClienteInOrdem(cliente);
		}
		stop();
	break;
	
	case 8:
		printf("\t|REALIZAR VENDA|\n");
		if(estaVaziaArvCliente(cliente) == 1 || estaVaziaArvProd(produto) == 1){
			printf("Ops... a lista de clientes ou o estoque se encontram vazios.\nVoc� ser� redirecionado para o menu principal.\n");
		} else {
			printf("Primeiramente insira um c�digo para identificar a venda: ");
			scanf("%d", &codigo_venda);
			venda = realizarVenda(venda,codigo_venda,cliente,produto);
			printf("Obrigado, volte sempre!\n");
		}
		stop();
	break;
	
	case 9:
		printf("\t|CONSULTAR VENDAS|\n");
		if(estaVaziaArvVenda(venda) == 1){
			printf("N�o foi realizada nenhuma venda ainda...\n");
		} else {
			imprimirVendas(venda);
		}
		stop();
	break;
	
	case 10:
		printf("\t|TOTAL DE VENDAS|\n");
		int totalvendas = vendasTotais(venda);
		printf("Quantidade de vendas realizadas hoje: %d \n", totalvendas);
		stop();
	break;
	
	case 11:
		deseja_sair = 1;
		printf("\t|SAIR|\nObrigado por usar nossos sistemas! At� j�!\n");
		stop();
	break;
	
	default:
		printf("\t|ERRO|\nInsira um comando v�lido.\n");
		stop();
	break;
	}
	system("cls");
}
}

/* -------------------------------------------------------------------------------------------------------------------------*/
// | �rea de desenvolvimento de fun��es| 
// | A �rea abaixo foi usada para o desenvolvimento das fun��es 
// | declaradas no in�cio do programa:

// Fun��o auxiliar STOP
void stop(){
	system("pause");
	system("cls");
}

// <<<--------------------------- Fun��es de PRODUTO --------------------------->>>
// Criar �rvore de produtos
ArvProd *criarArvProd(){
	return NULL;
}

// Verifica se a �rvore de produtos est� vazia
int estaVaziaArvProd(ArvProd *a){
	return (a==NULL)?1:0;
}

// Cria novo produto
ArvProd *novoProduto(int codigo){
	ArvProd *novo = (ArvProd*)malloc(sizeof(ArvProd));
	novo->codigo = codigo;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->altura = 1;
	printf("Nome do produto: ");
	fflush(stdin);
	fgets(novo->nome, 30,stdin);
	printf("Pre�o unit�rio: ");
	scanf("%f", &novo->valor);
	printf("Quantidade em estoque: ");
	scanf("%d", &novo->unidades);
	printf("Descri��o do produto: ");
	fflush(stdin);
	fgets(novo->descricao, 50, stdin);
	return novo;
}

// Insere produto na �rvore
ArvProd *inserirProd(ArvProd *a, int codigo){
	if(a == NULL){
		return novoProduto(codigo);
	}
	if(codigo < a->codigo){
		a->esq = inserirProd(a->esq, codigo);
	} else if (codigo > a->codigo){
		a->dir = inserirProd(a->dir, codigo);
	}
	else {
		return a;
	}
	
	a->altura = maximo(alturaArvProd(a->esq), alturaArvProd(a->dir)) + 1;
	int fb = fatorBalanceador(a);
	
	// Casos de rota��o:
	// LL
	if(fb > 1 && codigo < a->esq->codigo){
		return rotacaoR(a);
	}
	
	// RR
	if(fb < -1 && codigo > a->dir->codigo){
		return rotacaoL(a);
	}
	
	// RL
	if(fb < -1 && codigo < a->dir->codigo){
		a->dir = rotacaoR(a->dir);
		return rotacaoL(a);
	}
	
	// LR
	if(fb > 1 && codigo > a->esq->codigo){
		a->esq = rotacaoL(a->esq);
		return rotacaoR(a);
	}
	return a;
}

// Busca produto 
int buscarProd(ArvProd *a, int codigo_produto){
  if(estaVaziaArvProd(a) == 1){
    return 0;
  } else {
    if(codigo_produto == a->codigo){    								 // quando o valor � encontrado
      return 1;
    } else if(codigo_produto < a->codigo){ 							// lado esquerdo
      return buscarProd(a->esq, codigo_produto);
    } else { 																						// lado direito
      return buscarProd(a->dir, codigo_produto);
    }
  }
}

// Exibe estoque em In-Ordem
void exibirEstoqueInOrdem(ArvProd *a){
	if(estaVaziaArvProd(a) != 1){
	exibirEstoqueInOrdem(a->esq);
	printf("\nProduto: %sC�digo: %d\nValor: R$%.2f\nQuantidade em estoque: %d\n",a->nome, a->codigo, a->valor, a->unidades);
	exibirEstoqueInOrdem(a->dir);
	} 
}

// Compara dois n�s e retorna qual possui maior valor
int maximo(int x, int y){			
	return (x>y)?x:y;
}

// Calcula a altura da �rvore de Produto
int alturaArvProd(ArvProd *a){
	if(a == NULL){
		return 0;
	} 
	return alturaArvProd(a->esq) - alturaArvProd(a->dir);
}

// Rota��o L para ArvoreProd
ArvProd *rotacaoL(ArvProd *a){
	ArvProd *aux1 = a->dir;
	ArvProd *aux2 = aux1->esq;
	
	aux1->esq = a;
	a->dir = aux2;
	
	a->altura = maximo(alturaArvProd(a->esq), alturaArvProd(a->dir)) + 1;
	aux1->altura = maximo(alturaArvProd(aux1->esq), alturaArvProd(aux1->dir)) + 1;
	
	return aux1;
}

// Rota��o R para ArvoreProd
ArvProd *rotacaoR(ArvProd *a){
	ArvProd *aux1 = a->esq;
	ArvProd *aux2 = aux1->dir;
	
	aux1->dir = a;
	a->esq = aux2;
	
	a->altura = maximo(alturaArvProd(a->esq), alturaArvProd(a->dir)) + 1;
	aux1->altura = maximo(alturaArvProd(aux1->esq), alturaArvProd(aux1->dir)) + 1;
	
	return aux1;
}

// Calcula o fator de balanceamento da �rvore de Produto
int fatorBalanceador(ArvProd *a){
	if(a == NULL){
		return 0;
	}	
	return alturaArvProd(a->esq) - alturaArvProd(a->dir);
}

// <<<--------------------------- Fun��es de CLIENTE --------------------------->>>
// Rota��o L para �rvore Cliente
ArvCliente *rotacaoLC(ArvCliente *a){
	ArvCliente *aux1 = a->dir;
	ArvCliente *aux2 = aux1->esq;
	
	aux1->esq = a;
	a->dir = aux2;
	
	a->altura = maximo(alturaArvCliente(a->esq), alturaArvCliente(a->dir)) + 1;
	aux1->altura = maximo(alturaArvCliente(aux1->esq), alturaArvCliente(aux1->dir)) + 1;
	
	return aux1;
}

// Rota��o R para �rvore Cliente
ArvCliente *rotacaoRC(ArvCliente *a){
	ArvCliente *aux1 = a->esq;
	ArvCliente *aux2 = aux1->dir;
	
	aux1->dir = a;
	a->esq = aux2;
	
	a->altura = maximo(alturaArvCliente(a->esq), alturaArvCliente(a->dir)) + 1;
	aux1->altura = maximo(alturaArvCliente(aux1->esq), alturaArvCliente(aux1->dir)) + 1;
	
	return aux1;
}

// Cria �rvore de Cliente
ArvCliente *criarArvCliente(){
	return NULL;
}

// Verifica se a �rvore de Cliente est� vazia
int estaVaziaArvCliente(ArvCliente *a){
	return (a==NULL)?1:0;
}

// Cria um novo Cliente
ArvCliente *novoCliente(int codigo){
	ArvCliente *novo = (ArvCliente*)malloc(sizeof(ArvCliente));
	novo->codigo = codigo;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->altura = 1;
	
	printf("Nome do cliente: ");
	fflush(stdin);
	fgets(novo->nome, 30, stdin);
	printf("CPF: ");
	fflush(stdin);
	fflush(stdin);
	fgets(novo->cpf, 12,stdin);
	return novo;
}

// Insere o cliente criado na �rvore
ArvCliente *inserirCliente(ArvCliente *cliente, int codigo){
	if(cliente == NULL){
		return novoCliente(codigo);
	}
	if(codigo < cliente->codigo){
		cliente->esq = inserirCliente(cliente->esq, codigo);
	} else if (codigo > cliente->codigo){
		cliente->dir = inserirCliente(cliente->dir, codigo);
	}
	else {
		return cliente;
	}
	
	cliente->altura = maximo(alturaArvCliente(cliente->esq), alturaArvCliente(cliente->dir)) + 1;
	int fb = fatorBalanceadorC(cliente);
	
	// Casos de rota��o:
	// LL
	if(fb > 1 && codigo < cliente->esq->codigo){
		return rotacaoRC(cliente);
	}
	
	// RR
	if(fb < -1 && codigo >= cliente->dir->codigo){
		return rotacaoLC(cliente);
	}
	
	// RL
	if(fb < -1 && codigo < cliente->dir->codigo){
		cliente->dir = rotacaoRC(cliente->dir);
		return rotacaoLC(cliente);
	}
	
	// LR
	if(fb > 1 && codigo > cliente->esq->codigo){
		cliente->esq = rotacaoLC(cliente->esq);
		return rotacaoRC(cliente);
	}
	return cliente;
}

// Calcula a altura da �rvore de Cliente
int alturaArvCliente(ArvCliente *a){
		if(a == NULL){
		return 0;
	} 
	return alturaArvCliente(a->esq) - alturaArvCliente(a->dir);
}

// Calcula fator de balanceamento da �rvore de Cliente
int fatorBalanceadorC(ArvCliente *a){
	if(a == NULL){
		return 0;
	}	
	return alturaArvCliente(a->esq) - alturaArvCliente(a->dir);
}

// Busca um determinado cliente na �rvore
int buscarCliente(ArvCliente *a, int codigo_cliente){
	// Verifica se a �rvore est� vazia
  if(estaVaziaArvCliente(a) == 1){
    return 0;
  } else {
    if(codigo_cliente == a->codigo){     // quando o valor � encontrado
      return 1;
    } else if(codigo_cliente < a->codigo){ // lado esquerdo
      return buscarCliente(a->esq, codigo_cliente);
    } else { // lado direito
      return buscarCliente(a->dir, codigo_cliente);
    }
  }
}

// Remove um determinado cliente
ArvCliente *removerCliente(ArvCliente *a, int codigo_cliente){
	if(a==NULL){
		return a;
	}

	if(codigo_cliente < a->codigo){
		a->esq = removerCliente(a->esq,codigo_cliente);
	} else if(codigo_cliente > a->codigo){ 
		a->dir = removerCliente(a->dir,codigo_cliente);
	} else {
		
		if((a->dir == NULL) && (a->esq == NULL)){
			free(a);
			a = NULL;
		}	else if((a->esq != NULL) && (a->dir == NULL)){
			ArvCliente *aux = a->esq;
			a = a->esq;
			free(aux);
		} else if((a->dir != NULL) && (a->esq == NULL)){
			ArvCliente *aux = a->dir;
			a = a->dir;
			free(aux);
		} else {
			ArvCliente *aux = menor(a->dir);
			a->codigo = aux->codigo;
			a->dir = removerCliente(a->dir,aux->codigo);
		}
	}
	
	if(a==NULL){
		return a;
	}

	a->altura = maximo(alturaArvCliente(a->esq), alturaArvCliente(a->dir)) + 1;

	int fb = fatorBalanceadorC(a);

	// Casos de Rota��o
	// LL
	if((fb > 1) && (fatorBalanceadorC(a->esq) >= 0)){
		return rotacaoRC(a);
	}

	// RR
	if((fb < -1) && (fatorBalanceadorC(a->dir) <=0)){
		return rotacaoLC(a);
	}
	
	// LR
	if((fb > 1) && (fatorBalanceadorC(a->esq) < 0)){
		a->esq = rotacaoLC(a->esq);
		return rotacaoRC(a);
	}
	
	// RL
	if((fb < -1) && (fatorBalanceadorC(a->dir) > 0)){
		a->dir = rotacaoRC(a->dir);
		return rotacaoLC(a);
	}
	return a;
}

// Imprime os clientes cadastrados em IN-ORDEM
void exibirClienteInOrdem(ArvCliente *a){
	if(estaVaziaArvCliente(a) != 1){
	exibirClienteInOrdem(a->esq);
	printf("\nNome do cliente: %sC�digo de identifica��o: %d\nCPF: %s\n", a->nome, a->codigo, a->cpf);
	exibirClienteInOrdem(a->dir);
	} 
}

// Percorre a �rvore Cliente e retorna o menor valor encontrado (cliente)
ArvCliente *menor(ArvCliente *a){
	while(a->esq!=NULL){
		a = a->esq;
	}
	return a;
}

// <<<--------------------------- Fun��es de VENDA --------------------------->>>
// Cria �rvore de venda
ArvVenda *criarArvVenda(){
	return NULL;
}

// Verifica se a �rvore de VENDA est� vazia
int estaVaziaArvVenda(ArvVenda *a){
	return (a==NULL)?1:0;
}

// Cria nova venda
ArvVenda *criarVenda(int codigo, ArvCliente *c, ArvProd *p){
	ArvVenda *novo = (ArvVenda*)malloc(sizeof(ArvVenda));
	novo->codigo_venda = codigo;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->altura = 1;
	
	int codigo_cliente, codigo_produto;
	ArvCliente *busca_cliente;
	ArvProd *busca_produto;
	int qtd_produto;
	
	printf("Insira o c�digo de identifica��o do cliente: ");
	scanf("%d", &codigo_cliente);
	busca_cliente = buscarClienteParaVenda(c, codigo_cliente);
	if(busca_cliente == NULL){
		printf("Cliente n�o encontrado... Voc� ser� redirecionado para o menu principal.\n");
	} else {
		printf("Agora, insira o c�digo de identifica��o do produto: ");
		scanf("%d", &codigo_produto);
		busca_produto = buscarProdParaVenda(p, codigo_produto);
		if(busca_produto == NULL){
			printf("Produto n�o encontrado... Voc� ser� redirecionado para o menu principal.\n");
		} else {
			printf("Insira a quantidade desejada: ");
			scanf("%d", &qtd_produto);
			if(qtd_produto <= p->unidades){
				strcpy(novo->cpf, busca_cliente->cpf);
				strcpy(novo->nome_comprador, busca_cliente->nome);
				novo->codigo_produto = codigo_produto;
				novo->valor = qtd_produto * busca_produto->valor;
				busca_produto->unidades = busca_produto->unidades-qtd_produto;
				printf("Valor total a pagar: %.2f. Siga para o caixa!\n", novo->valor);
				return novo;
			} else {
				printf("Quantidade n�o dispon�vel no estoque.\n");
			}
		}
	}
}

// Insere a venda criada na �rvore de Vendas
ArvVenda *realizarVenda(ArvVenda *venda, int codigo, ArvCliente *c, ArvProd *p){
		if(venda == NULL){
			ArvCliente *cliente = c;
			ArvProd *produto = p;
		return criarVenda(codigo, cliente, produto);
	}
	if(codigo < venda->codigo_venda){
		venda->esq = realizarVenda(venda->esq, codigo, c, p);
	} else if (codigo > venda->codigo_venda){
		venda->dir = realizarVenda(venda->dir, codigo, c, p);
	}
	else {
		return venda;
	}
	
	venda->altura = maximo(alturaArvVenda(venda->esq), alturaArvVenda(venda->dir)) + 1;
	int fb = fatorBalanceadorV(venda);
	
	// Casos de rota��o:
	// LL
	if(fb > 1 && codigo < venda->esq->codigo_venda){
		return rotacaoRV(venda);
	}
	
	// RR
	if(fb < -1 && codigo >= venda->dir->codigo_venda){
		return rotacaoLV(venda);
	}
	
	// RL
	if(fb < -1 && codigo < venda->dir->codigo_venda){
		venda->dir = rotacaoRV(venda->dir);
		return rotacaoLV(venda);
	}
	
	// LR
	if(fb > 1 && codigo > venda->esq->codigo_venda){
		venda->esq = rotacaoLV(venda->esq);
		return rotacaoRV(venda);
	}
	return venda;
}

// Calcula altura da Arv Venda
int alturaArvVenda(ArvVenda *a){
		if(a == NULL){
		return 0;
	} 
	return alturaArvVenda(a->esq) - alturaArvVenda(a->dir);
}

// Rota��o para a Esquerda na �rvore de Vendas
ArvVenda *rotacaoLV(ArvVenda *a){
	ArvVenda *aux1 = a->dir;
	ArvVenda *aux2 = aux1->esq;
	
	aux1->esq = a;
	a->dir = aux2;
	
	a->altura = maximo(alturaArvVenda(a->esq), alturaArvVenda(a->dir)) + 1;
	aux1->altura = maximo(alturaArvVenda(aux1->esq), alturaArvVenda(aux1->dir)) + 1;
	
	return aux1;
}

// Rota��o para a Direita na �rvore de Vendas
ArvVenda *rotacaoRV(ArvVenda *a){
	ArvVenda *aux1 = a->esq;
	ArvVenda *aux2 = aux1->dir;
	
	aux1->dir = a;
	a->esq = aux2;
	
	a->altura = maximo(alturaArvVenda(a->esq), alturaArvVenda(a->dir)) + 1;
	aux1->altura = maximo(alturaArvVenda(aux1->esq), alturaArvVenda(aux1->dir)) + 1;
	
	return aux1;
}

// Calcular Fator de Balanceamento na �rvore de Vendas 
int fatorBalanceadorV(ArvVenda *a){
	if(a == NULL){
		return 0;
	}	
	return alturaArvVenda(a->esq) - alturaArvVenda(a->dir);
}

// Imprime as vendas realizadas em IN-ORDEM
void imprimirVendas(ArvVenda *a){
	if(estaVaziaArvVenda(a) != 1){
	imprimirVendas(a->esq);
	printf("\nNome do cliente: %sCPF: %s\nValor total: %2.f\nC�digo da venda: %d\nC�digo do produto: %d\n", a->nome_comprador, a->cpf, a->valor, a->codigo_venda, a->codigo_produto);
	imprimirVendas(a->dir);
	} 
}

// <<<-------------------------- FUN��ES DE BUSCA AUXILIARES NA FUN��O DE VENDA -------------------------->>>
// Busca um produto na �rvore de produtos e retorna.
// Essa fun��o foi criada j� que a outra vers�o da mesma
// retorna um valor int.
// No caso, essa nova fun��o de busca retorna o produto 
// buscado, caso encontrado. 
// Isso permite sua manipula��o dentro da �rvore de Vendas ;
ArvProd *buscarProdParaVenda(ArvProd *a, int codigo){
  if(estaVaziaArvProd(a)){
    return NULL;
  } else {
    if(codigo == a->codigo){     // quando o valor � encontrado
      return a;
    } else if(codigo < a->codigo){ // lado esquerdo
      return buscarProdParaVenda(a->esq, codigo);
    } else { // lado direito
      return buscarProdParaVenda(a->dir, codigo);
    }
  }
}

// O mesmo ocorre na fun��o abaixo por�m em rela��o aos Clientes.
// Desta forma, torna-se poss�vel a manipula��o dos dados de clientes
// na �rvore de Vendas.
ArvCliente* buscarClienteParaVenda(ArvCliente *a, int codigo){
	if(estaVaziaArvCliente(a)){
    return NULL;
  } else {
    if(codigo == a->codigo){     // quando o valor � encontrado
      return a;
    } else if(codigo < a->codigo){ // lado esquerdo
      return buscarClienteParaVenda(a->esq, codigo);
    } else { // lado direito
      return buscarClienteParaVenda(a->dir, codigo);
    }
  }
}

// Calcula o total de vendas realizadas 
int vendasTotais(ArvVenda *a){
	if(a == NULL){
		return 0;
	} else {
		return 1 + vendasTotais(a->esq) + vendasTotais(a->dir);
	}	
}
