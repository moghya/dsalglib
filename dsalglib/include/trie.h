/*
	Created by kauziishere on 02/09/2018
*/
#ifndef DSALGLIB_TRIE_H
#define DSALGLIB_TRIE_H

#include "trie.h"
namespace dsa
{
    class trie{
    	private:
    		struct trienode{
    			trienode* next[26];
    			bool isword;
    			trienode(bool isword = false){
    				int i;
    				for(i = 0; i < 26; i++)
    					this->next[i] = nullptr;
    				this->isword = isword;
    			}
    		};
    		
    		
    		
    		trienode* root;
    		long long int count;
    		
    		/*
    			Function: create a Trie node
    			Pre: isword a boolean variable to denote whether the character is end of a word
    			Post: return trienode
    		*/
    		
    		trienode* create_node(bool isword){
    			trienode* node = new trienode(isword);
    			return node;
    		}
    		
    		/*
    			Function: calculate length of a word
    			Pre: Word as a character array
    			Post: return length of the word
    		*/
    		long long int calculate_length_of_a_word(char* word){
    			long long int n = 0;
    			while(word[n] != '\0')
    				n++;
    			return n;
    		}
    		
    		/*
    			Function: inserts a word in trie
    			Pre: treeroot root the trie, characters word of the trie nodes
    			Post: returns nothing
    		*/
    		
    		trienode* _insert(trienode* trieroot, char* word){
    			long long int i = 0, n = 0;
    			trienode* temp = trieroot;
    			n = calculate_length_of_a_word(word);
    			if(temp == nullptr){
    				trieroot = this->create_node(false);
    				temp = trieroot; 
    			}
    			while(i < n){
   					trienode* node;
   					if(temp->next[word[i]-'a'] == nullptr){
						temp->next[word[i]-'a'] = create_node(false);
					}
					temp = temp->next[word[i]-'a'];
					i++;
    			}
    			temp->isword = true;
    			return trieroot;
    		}
    		
    		/*
    			Function: Check if word exists in the trie
    			Pre: Root of trie as trieroot and word as a char pointer
    			Post: Return boolean true is word is found and false if word is not found
    		*/
    		
    		bool _check_if_word_exist(trienode* trieroot, char* word){
    			long long int i = 0, n = 0;
    			trienode* temp = trieroot;
    			n = calculate_length_of_a_word(word);
    			while(temp != nullptr && i < n){
    				if(temp->next[word[i]-'a'] == nullptr)
    					return false;
    				temp = temp->next[word[i]-'a'];
    				i++;
    			}
    			if(temp->isword == true)
    				return true;
    			return false;
    		}
    	public:
    		trie(){
    			root = nullptr;
    		}
    		
    		void insert(char* word){
    			root = this->_insert(root, word);
    			return;
    		}
    		
    		bool search(char* word){
    			return (this->_check_if_word_exist(root, word));
    		}
    };
}
#endif
