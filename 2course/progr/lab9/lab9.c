#include <stdio.h>
#include <string.h>


struct SalesOrderDetail {
    int SalesOrderID;
    int SalesOrderDetailID;
    int OrderQty;
    int ProductID;
    float UnitPrice;
    float UnitPriceDiscount;
    char ModifiedDate[20];
} ;
struct SalesOrderDetail S[1000];
// Объявление узла двоичного дерева.
struct BTree
{
    double szText;
    struct BTree *Left;
    struct BTree *Right;
    struct BTree *Parent;
};



struct BTree* create_node( double name)
{
    struct BTree *node;

    node = malloc(sizeof(struct BTree));

    if (node)
    {
        node->szText= name;

        node->Left = NULL;
        node->Right = NULL;
        node->Parent= NULL;
    }

    return node;
}

struct BTree* insert(struct BTree*tree, struct BTree* node)
{
    int cmp;

    if (tree == NULL)
        return node;

   if ( node->szText> tree->szText) cmp=1 ; else cmp=-1;
    if (cmp == 0)
    {

    }
    else if (cmp < 0)
    {
        tree->Left = insert(tree->Left, node);

    }
    else
    {
        tree->Right = insert(tree->Right, node);
    }

    return tree;
}

/*struct BTree* insert(struct BTree* x, struct BTree* z)            // x — корень поддерева, z — вставляемый элемент
 {  while (x != NULL)
    { if (z->szText > x->szText)
        if (x->Right != NULL)
           x = x->Right;
        else
           {z->Parent = x;
           x->Right = z;
           break;
        }
     else
            if (z->szText < x->szText)
        if( x->Left != NULL)
           x = x->Left;
        else
          { z->Parent = x;
           x->Left = z;
           break;}
    }
    return z;
}*/




void PrintTree( struct BTree* btRoot )
{
    // Пройти левое поддерево (в обратном порядке).
    if( btRoot->Left )
        PrintTree( btRoot->Left );

    // Попасть в корень.
   printf("%lf\n",btRoot->szText);

    // Пройти правое поддерево (в обратном порядке).
    if( btRoot->Right )
        PrintTree( btRoot->Right );
    //system("1.txt");
}

int menu()
{
    int i=0;
    printf("Choose number of paragraph for working:\n");
    printf("1)SalesOrderID\n");
    printf("2)SalesOrderDetailID\n");
    printf("3)OrderQty\n");
    printf("4)ProductID\n");
    printf("5)UnitPrice\n");
    printf("6)UnitPriceDiscount\n");
    printf(">>");
    scanf("%d",&i);

    return i;
}

int menu2()
{
    int i=0;
    printf("Choose function:\n");
    printf("1)Print:\n");
    printf("2)Min:\n");
    printf("3)Max:\n");
    printf("4)Successor\n");
    printf("5)Predecessor\n");
    printf("6)Delete\n");
    printf("7)Pre-order\n");
    printf("8)In-order\n");
    printf("9)Post-order\n");
    printf(">>");
    scanf("%d",&i);

    return i;

}

struct BTree * search (struct BTree * tree, double key)
{
   struct SalesOrderDetail  *buf;

    if (tree)
        do
        {
            buf=tree;
            if (tree->szText==key)
                return NULL;
            if (key<tree->szText)
                tree=tree->Left;
            else
                tree=tree->Right;
        } while (tree);

        return buf;
}
void print_Tree(struct BTree * p,double level,FILE *f)
{

    if(p)
    {
        print_Tree(p->Left,level + 1,f);
        for(int i = 0;i< level;i++) fprintf(f,"___");
        fprintf(f,"%lf\n",p->szText) ;
        if (p->szText==71776) print("!!!!!!!!!");
        print_Tree(p->Right,level + 1,f);
    }

    return;
}

double min(struct BTree* x)
{
double min1;
    while (x->Left!= NULL)
 {
        min1=x->szText;
        x=x->Left;
}
    return min1;
}

double max(struct BTree* x)
{
double max1;
    while (x->Right!= NULL)
 {
        max1=x->szText;
        x=x->Right;
}
    return max1;
}
double next(double  x,struct BTree* root)
 { struct BTree* current = root, *successor = NULL   ;             // root — корень дерева
   while (current != NULL)
      {if (current->szText > x)
        { successor = current;
         current = current->Left;}
      else
         current = current->Right;
      }
   return successor->szText;
 }
double prev(double  x,struct BTree* root)
 { struct BTree* current = root, *successor = NULL   ;             // root — корень дерева
   while (current != NULL)
      {if (current->szText < x)
        { successor = current;
         current = current->Right;}
      else
         current = current->Left;
      }
   return successor->szText;
 }

///ОБХОДЫ
void print(struct BTree *node, void *param)
{
    static i=0;
    i++;
    const char *fmt = param;
    if(!(i%5)) printf("\n");
    printf(fmt, node->szText);

}
void apply_pre(struct BTree* tree, void (*f)(struct BTree*, void*), void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    apply_pre(tree->Left, f, arg);
    apply_pre(tree->Right, f, arg);
}

void apply_in(struct BTree *tree, void (*f)(struct BTree*, void*), void *arg)
{
    if (tree == NULL)
        return;

    apply_in(tree->Left, f, arg);
    f(tree, arg);
    apply_in(tree->Right, f, arg);
}

void apply_post(struct BTree* tree, void (*f)(struct BTree*, void*), void *arg)
{
    if (tree == NULL)
        return;

    apply_post(tree->Left, f, arg);
    apply_post(tree->Right, f, arg);
    f(tree, arg);
}
struct BTree *dtree(struct BTree  *root, double key)
{
  struct BTree   *p,*p2;

  if(!root) return root; /* вершина не найдена */

  if(root->szText == key) { /* удаление корня */
    /* это означает пустое дерево */
      printf("combo\n");
    if(root->Left == root->Right){
      free(root);
      return NULL;
    }
    /* или если одно из поддеревьев пустое */
    else if(root->Left == NULL) {
      p = root->Right;
      free(root);
      printf("combo1\n");
      return p;
    }
    else if(root->Right == NULL) {
      p = root->Left;
      free(root);
      printf("combo2\n");
      return p;
    }
    /* или есть оба поддерева */
    else {
      p2 = root->Right;
      p = root->Right;
      while(p->Left) p = p->Left;
      p->Left = root->Left;
      free(root);
      printf("combo3\n");
      return p2;
    }
  }
  if(root->szText < key) root->Right = dtree(root->Right, key);
  else root->Left = dtree(root->Left, key);
  return root;
}

int main()
{
    FILE *f;
       int len=0;
    FILE *fp=fopen("SalesOrderDetails.xml","r");
        char s[100];
        char * pch;
        fgets(s,99,fp);
        strcpy(s,"");
        int i=0;
        while(1)
        {
            len++;
         fgets(s,99,fp);
         if (!strcmp(s,"</ROOT>")) break;
         strcpy(s,"");
          fgets(s,99,fp);//первый
           pch = strtok (s,"<SalesOrderID>");
           pch = strtok (NULL,"<\SalesOrderID>");
           S[i].SalesOrderID=atoi(pch);
           strcpy(s,"");
           fgets(s,99,fp); //второй
           pch = strtok (s,"<SalesOrderDetailID>");
           pch = strtok (NULL,"<\\SalesOrderDetailID>");
           S[i].SalesOrderDetailID=atoi(pch);
           strcpy(s,"");
           fgets(s,99,fp); //третий
           pch = strtok (s,"<OrderQty>");
           pch = strtok (NULL,"<\\OrderQty>");
           S[i].OrderQty=atoi(pch);

           strcpy(s,"");
           fgets(s,99,fp); //четвертый
           pch = strtok (s,"<ProductID>");
           pch = strtok (NULL,"<\\ProductID>");
           S[i].ProductID=atoi(pch);
           strcpy(s,"");
           fgets(s,99,fp); //пятый
           pch = strtok (s,"<UnitPrice>");
           pch = strtok (NULL,"<\\UnitPrice>");
           S[i].UnitPrice=atof(pch);

           //printf("%lf\n",atof(pch));
           strcpy(s,"");
           fgets(s,99,fp); //шестой
           pch = strtok (s,"<UnitPriceDiscount>");
           pch = strtok (NULL,"<\\UnitPriceDiscount>");
           S[i].UnitPriceDiscount=atof(pch);
           // printf("%sH %lf \n",pch,atof(pch));
           strcpy(s,"");
           fgets(s,99,fp); //седьмой
           pch = strtok (s,"<ModifiedDate>");
           pch = strtok (NULL,"<\\ModifiedDate>");
            strcpy(S[i].ModifiedDate,pch);
           strcpy(s,"");
           fgets(s,99,fp);
           strcpy(s,"");
           i++;
    }
        //считатали файл в массив и перегоняем в числовой массив, из которого построим дерево
           int par=menu();
           double yy[len];
           switch (par)
           {
               case 1:
              {
                  for(int i=0;i<len;i++)
                      yy[i]=1.0*S[i].SalesOrderID;
                  break;
              };

              case 2:
             {
              for(int i=0;i<len;i++)
                  yy[i]=1.0*S[i].SalesOrderDetailID;
              break;
             };
               case 3:

              {
               for(int i=0;i<len;i++)
                   yy[i]=1.0*S[i].OrderQty;
               break;
              };

               case 4:
              {
               for(int i=0;i<len;i++)
                   yy[i]=1.0*S[i].ProductID;
               break;
              };

               case 5:
              {
               for(int i=0;i<len;i++)
                   yy[i]=1.0*S[i].UnitPrice;
               break;
              };
               case 6:
              {
               for(int i=0;i<len;i++)
                   yy[i]=1.0*S[i].UnitPriceDiscount;
               break;
              };


           }
           //len++;
           fclose(fp);
// наполнение дерева
    struct BTree *root=NULL;
    struct BTree *node;
    for(int i=0;i<len;i++)
        {
        node = create_node(yy[i]);
        //printf("Name %lf",node->szText);
       // printf("one");
       root = insert(root, node);

    }
    do
    {
        int u=menu2();
        switch (u)
        {
            case 1:
            {
                f = fopen("file1.txt", "w");
                print_Tree(root,0,f);

                printf("You can watch the tree in file1.txt\n");
                break;
            }
            case 2:
            {
              printf("Minimum %lf\n",min(root));
              break;
            }
            case 3:
            {
              printf("Maximum %lf\n",max(root));
              break;
            }
            case 4:
            {
               printf("input element:");
               double b;
               scanf("%lf",&b);
              printf("Next %lf\n",next(b,root));
              break;
            }
            case 5:
            {
              //
                printf("input element:");
                double b;
                scanf("%lf",&b);
               printf("Prev %lf\n",prev(b,root));
              break;
            }
            case 7:{
                printf("Pre-order:\n");
                apply_pre(root, print, "%8.1lf ");
                printf("\n");
                break;
            }
            case 8:{
                printf("In-order:\n");
                apply_in(root, print, "%8.1lf ");
                printf("\n");
                break;
            }
            case 9:{
                printf("Post-order:\n");
                apply_post(root, print, "%8.1lf ");
                printf("\n");
                break;
            }
            case 6:{
                printf("input element:");
                double b;
                scanf("%lf",&b);

                //printf("Name %lf",node->szText);
               // printf("one");
               root = dtree(root, b);
               len--;
               break;

            }

        }

        printf("");


    }while (1);

    return 0;
}
