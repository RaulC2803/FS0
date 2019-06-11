#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <functional>

using namespace std;
using namespace System;

class CDatos
{
	string Nombre;
	string Apellido;
	int Año;

public:
	CDatos() {
		Nombre = "";
		Apellido = "";
		Año = 0;
	}

	void MostrarDatos()
	{
		cout << Nombre << "\t" << Apellido << " \t" << Año;
	}

	void setNombre(string n) { Nombre = n; }
	void setApellido(string a) { Apellido = a; }
	void setAño(int año) { Año = año; }

};

class Fila
{
	vector<CDatos*>*Filas;
public:
	Fila() {
		Filas = new vector<CDatos*>;
	}
	void GenerarDatos()
	{
		for (int i = 0; i < 5; i++)
		{
			Filas->push_back(new CDatos());
		}
	}

};

class DataFrame
{
	vector<CDatos*>*Filas;
public:
	DataFrame() {
		Filas = new vector<CDatos*>;
	}
	void GenerarDatos()
	{
		for (int i = 0; i < 5; i++)
		{
			Filas->push_back(new CDatos());
		}
	}
	void MostrarFilas() {
		for (int i = 0; i < Filas->size(); i++)
		{
			cout << i << " " ; Filas->at(i)->MostrarDatos(); cout << endl;
		}
	}
	bool LecturaDatos(string Archivo)
	{
		int i = 0;
		ifstream file;

		file.open(Archivo, ios::in);

		if (file.fail()) { cout << "ERROR AL ABRIR EL ARCHIVO" << endl; return false; }

		while (file.good() && i < Filas->size())
		{
			string nombre = "";
			string apellido = "";
			string año = "";
			if (Archivo.at(Archivo.size() - 3) == 'c')
			{
				getline(file, nombre, ',');
				getline(file, apellido, ',');
				getline(file, año, '\n');
			}
			else
			{
				getline(file, nombre, '\t');
				getline(file, apellido, '\t');
				getline(file, año, '\n');
			}
			Filas->at(i)->setNombre(nombre);
			Filas->at(i)->setApellido(apellido);
			Filas->at(i)->setAño(atoi(año.c_str()));
			i++;
		}
		file.close();
		return true;
	}
};

class Tree
{
	struct Node
	{
		float elem;
		Node* left;
		Node* right;

		Node(float elem, Node* left = nullptr, Node* rigth = nullptr) :elem(elem), left(left), right(right) {}
	};

	Node* root;
	int length;

	void borrar(Node* node)
	{
		if (node != nullptr) {
			borrar(node->left);
			borrar(node->right);
			delete node;
		}
	}

	void add(Node*& node, float elem) {
		if (node == nullptr)
		{
			node = new Node(elem);
		}
		else if (elem < node->elem) {
			add(node->left, elem);
		}
		else {
			add(node->right, elem);
		}
	}

	void InOrder(Node* node, std::function<void(float)> doSomething) {
		if (node != nullptr)
		{
			InOrder(node->left, doSomething);
			doSomething(node->elem);
			InOrder(node->right, doSomething);
		}
	}

	Node* Mayor(Node* node) {
		if (node != nullptr) {
			if (node->right == nullptr) {
				return node;
			}
			else {
				return node->right;
			}
		}
		return nullptr;
	}
public:

	Tree() :root(nullptr), length(0) {}
	~Tree() { borrar(root); }

	void add(float elem) { add(root, elem); length++; }

	void InOrder(std::function<void(float)>doSomething)
	{
		InOrder(root, doSomething);
	}

	float Mayor() {
		Node* node = Mayor(root);
		if (node != nullptr) {
			return node->elem;
		}
	}

};