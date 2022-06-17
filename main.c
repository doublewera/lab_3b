//�������� �.� �20-�02
//
//������� 5 
//�������� ��������� ��� ������ � ������������ ��������, ������������ ������������� ���������, �� �������� ���������.
//������������ ������� ������������ ��������; ������ ������� ������� ����� ��������� ��������� :
//struct Item {
//	int busy;		/* ������� ��������� ��������*/
//	int key;		/* ���� ��������				*/
//	char* info;	/* ��������� �� ����������	
//};
//
//������������ ������ ������� ���������(��� ������� ������������� ������� ������� ������������ ��������� � ��������, const int SIZE = ...;).
//��� ������� � ��������� ������� ������������ ������� �����������.
//������������� ��������� �������� :
//-	��������� ������ �������� � ������� ��� �������, ��� � ������� �� ����� ���� ���� ��������� � ����������� �������; ���� ��� ��������� ������
//�������� ��������� ����� ��������, �� ����� ������ ���� �������� ��������� �� ������;
//-	�������� �� ������� ��������, ��������� ����� ������;
//-	����� �������� �� ��������� �����.����������� ������ ������ ���� ����� ������� �������, ���������� ��������� �������.���� �������� ������� �
//������� �����������, ������� �� ����� ��������� �� ������;
//-	����� ����������� ������� �� �����.
//����������� ��� �������� ��������� :
//a)	� ���� �������, � ����������, ����������� � �������� �������, �������� � �������� ������;
//b)	� ���� �������, � ����������, ����������� � �������� �������, �������� �� ������� ������(������������ �������� ���� ������������� �������).
//��� �������� ����������� � ��������, ����������� � �������� ������.������� ����������� �� �����(��� ��������� � ������ ���) � ������ ������ ������ 
//� ������������ � ���� � ����� ������ ������.����������, ����������� � �������� �������, ������������ � ���� ����� �� ��� ���������� �������� ���������
//� �������.��� ����� �������� �� ������� �� ���������.

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "hash_table.h"
#include "utilits.h"

FILE* prepare_arg_file(char** file_name) {
	int len = 1;
	*file_name = (char*)malloc(len);
	char c;

	//rewind(stdin);
	//��� �������� ����� �����
	printf("Input file name or emty line for entering from keyboard . . . ");
	while ((c = getchar()) != '\n') {
		(*file_name)[len - 1] = c;
		len++;
		*file_name = (char*)realloc(*file_name, len);
	}
	(*file_name)[len - 1] = '\0';
	return fopen(*file_name, "rb");
}

void save_and_close_file(FILE* f, char* file_name) {
	char c = '\0';
	int empty = 0;
	//��� ����� ����� ������� �� ��������� ����
	if (f != NULL) {
		fclose(f);
	}
	f = fopen(file_name, "wb"); //���� ��������� ������������� �������� ����� �����
	fwrite(&capacity, sizeof(int), 1, f);
	for (int i = 0; i < capacity; i++) {
		if (vector[i].info != NULL) {
			fwrite(&vector[i].key, sizeof(int), 1, f);
			fwrite(&vector[i].busy, sizeof(int), 1, f);
			fwrite(vector[i].info, sizeof(char), vector[i].size, f);
		}
		else {
			fwrite(&empty, sizeof(int), 1, f);
			fwrite(&empty, sizeof(int), 1, f);
			fwrite(&c, 1, 1, f);
		}
	}
	fclose(f);
}

int main()
{	
	capacity = 5;//��������� ��������� - ��� ��������
	int choice = 0, availability = 0;
	key_t key = 0;
	//������������� �����
	char* file_name = NULL;
	FILE* f = prepare_arg_file(&file_name);
	
	if (file_name[0] == 0) {
		printf("File name is empty, reading from keyboard.");
	}
	else {
		if (f == NULL) {
			printf("File not found. Reading from keyboard.");
		}
	}

	if (f != NULL) {
		capacity = get_size_f(f);
	}
	else {
		capacity = get_size();
	}
	if (capacity == 0) {
		printf("No NULL table");
		return -1;
	}
	
	init_table(capacity);
	if (f != NULL) {
		for(int i = 0; i < capacity; i++)
		insert(i, capacity, f);
	}

	do {
		print_menu();
		choice = select_action(choice);
		//system("pause");
		if (choice == EXIT)
			break;
		if (choice == ADD_ELEMENT)
		{
			key = get_key(key);

			availability = insert(key, capacity, f);
				if (availability == -1)
					duplicated_key();
				if (availability == -2)
					full_table();
		}
		if (choice == DELETE_ELEMENT)
		{
			key = get_key(key);

			availability =  delete_element(key, capacity);
			if (availability == -1) {
				not_found();
			}
			else
				printf("deleted");
		}
		if (choice == FIND_ELEMENT)
		{
			key = get_key(key);
			availability = search(key, capacity);
			if (availability == -1) {
				not_found();
			}
			else
				show_element(availability);
		}
		if (choice == SHOW_TABLE)
		{
			print_table(capacity);
		}
	} while (choice != 0);
	
	save_and_close_file(f, file_name);
	free(vector->info);
	free(vector);

	system("pause");
	return 0;
}