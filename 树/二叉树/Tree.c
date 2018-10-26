#include"pch.h"
#include"BinaryTree.h"

void initNodePre(BinaryTree **root) {//扩展二叉树前序创建
	*root = (BinaryTree *)malloc(sizeof(BinaryTree));
	BinaryTree *node = *root;
	scanf("%c", &node->c);
	if (node->c != '#') {
		initNodePre(&node->LeftChild);
		initNodePre(&node->RightChild);
	}
	else {
		node->LeftChild = NULL;
		node->RightChild = NULL;
	}
}

void preOrder(BinaryTree *root) {
	if (!root)
		return;
	printf("%c", root->c);
	preOrder(root->LeftChild);
	preOrder(root->RightChild);
}

void midOrder(BinaryTree *root) {
	if (!root)
		return;
	midOrder(root->LeftChild);
	printf("%c", root->c);
	midOrder(root->RightChild);
}

void postOrder(BinaryTree *root) {
	if (!root)
		return;
	postOrder(root->LeftChild);
	postOrder(root->RightChild);
	printf("%c",root->c);
}

void levelOrderRe(Queue *q) {//使用队列递归层序遍历
	if (q->front == q->rear)
		return;
	BinaryTree t;
	quitQueue(q, &t);
	printf("%c", t.c);
	if (t.LeftChild)
		enterQueue(q, *t.LeftChild);
	if (t.RightChild)
		enterQueue(q, *t.RightChild);
	levelOrderRe(q);
}

void levelOrder(Queue *q) {
	while (q->front != q->rear) {
		BinaryTree t;
		quitQueue(q, &t);
		printf("%c", t.c);
		if (t.LeftChild)
			enterQueue(q, *t.LeftChild);
		if (t.RightChild)
			enterQueue(q, *t.RightChild);
	}
}

void levelOrderInQueue(BinaryTree *root) {//队列实现二叉树层序遍历
	Queue *q = NULL;
	initQueue(&q);
	enterQueue(q, *root);
	levelOrder(q);
	//levelOrderRe(q);
}

void preOrderInStackRe(Stack *s) {
	if (isEmpty(s))
		return;
	BinaryTree t;
	pop(s, &t);
	printf("%c", t.c);
	if (t.RightChild)
		push(s, *t.RightChild);
	if(t.LeftChild)
		push(s, *t.LeftChild);
	preOrderInStackRe(s);
}

void preOrderInStackNoRe(Stack *s) {
	BinaryTree t;
	while (!isEmpty(s)) {
		pop(s, &t);
		printf("%c", t.c);
		if(t.RightChild)
			push(s, *t.RightChild);
		if(t.LeftChild)
			push(s, *t.LeftChild);
	}
}

void preOrderInStack(BinaryTree *root) {
	Stack *s = NULL;
	initStack(&s);
	push(s, *root);
	preOrderInStackNoRe(s);
}

void midOrderInStackRe(Stack *s) {
	if (s->top == -1)
		return;
	BinaryTree top;
	getTop(s,&top);
	if (top.LeftChild) {
		top = *top.LeftChild;
		push(s, top);
		midOrderInStackRe(s);
	}
	if (pop(s, &top))
		printf("%c", top.c);
	if (top.RightChild) {
		top = *top.RightChild;
		push(s, top);
		midOrderInStackRe(s);
	}
	if (pop(s, &top))
		printf("%c", top.c);
}

void midOrderInStackNoRe(Stack *s) {
	BinaryTree t;
	while (!isEmpty(s)) {
		while(getTop(s, &t), t.LeftChild)
			push(s, *t.LeftChild);
		if(pop(s, &t))
			printf("%c", t.c);
		if(pop(s, &t))
			printf("%c", t.c);
		if(t.RightChild)
			push(s, *t.RightChild);
	}
}

void midOrderInStack(BinaryTree *root) {
	Stack *s = NULL;
	initStack(&s);
	push(s, *root);
	midOrderInStackRe(s);
}

int main() {

	BinaryTree *root = NULL;
	initNodePre(&root);
	printf("递归前序遍历：");
	preOrder(root);
	printf("\n递归中序遍历：");
	midOrder(root);
	printf("\n递归后序遍历：");
	postOrder(root);
	printf("\n队列层序遍历：");
	levelOrderInQueue(root);//扩展前序序列
	printf("\n栈中前序遍历：");
	preOrderInStack(root);
	printf("\n栈中中序遍历：");
	midOrderInStack(root);
	return 0;
}