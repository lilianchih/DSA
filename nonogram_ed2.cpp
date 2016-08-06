#include <cstdlib>
#include <iostream>
#include <vector>
#include <stdio.h>
//#include <stack>

using namespace std;

bool next_re_comb(int* recomb, const int n, const int k) {
    int i = k - 1;
    do
        recomb[i]++;
    while (recomb[i] > n - 1 && i--);
    if (recomb[0] > n - 1)
        return 0;
    while (++i < k)
        recomb[i] = recomb[i - 1];
    return 1;
}

void possibilities(vector< vector<int> > *cells, int width, vector<int> *clues)
{
    int sum = 0;
    for(int i=0; i<clues->size(); i++){
            sum += clues->at(i);
    }
    int blanks = width - sum - (clues->size() - 1);
    
    if(blanks != 0){
    int *recomb = new int[blanks];
    for (int i = 0; i < blanks; i++)
        recomb[i] = 0;
    do{
        vector<int> temp1, temp2;
        for(int i=0; i<clues->size(); i++){
            if(i == 0)
                temp1.push_back(0);
            temp1.push_back(clues->at(i));
            if(i != clues->size() - 1)
                temp1.push_back(-1);
            else
                temp1.push_back(0);
        }
        for (int i = 0; i < blanks; ++i){
            temp1.at(2*recomb[i])--;
        }
        for(int i=0; i<temp1.size(); i++){
            if(temp1[i] > 0){
                for(int j=0; j<temp1[i]; j++)
                    temp2.push_back(1);
            }
            else{
                for(int j=0; j<(-temp1[i]); j++)
                    temp2.push_back(-1);
            }
        }
        cells->push_back(temp2);
    }
    while (next_re_comb(recomb, clues->size()+1, blanks));
    //delete[] recomb;
    }
    else{
        vector<int> temp;
        temp.reserve(width);
        for(int i=0; i<clues->size(); i++){
            for(int j=0; j<clues->at(i); j++)
                temp.push_back(1);
            if(i != clues->size() - 1)
                temp.push_back(-1);
        }

        cells->push_back(temp);
    }
    return ;
}

void eliminate(vector< vector<int> > *cells, int index, bool row_or_column, int width, int **diagram)
{
    if(row_or_column){
        int i = 0;
        while(i < cells->size()){
            for(int j=0; j<width; j++){
                if(diagram[index][j] != 0 && (*cells)[i][j] != diagram[index][j]){
                    cells->erase(cells->begin()+i);
                    break;
                }
                if(j == width - 1)
                    i++;
            }
        }
    }
    else{
        int i = 0;
        while(i < cells->size()){
            for(int j=0; j<width; j++){
                if(diagram[j][index] != 0 && (*cells)[i][j] != diagram[j][index]){
                    cells->erase(cells->begin()+i);
                    break;
                }
                if(j == width - 1)
                    i++;
            }
        }
    }
}

bool confirm(vector< vector<int> > *cells, int index, bool row_or_column, int width, int **diagram)
{
    bool changed = false;
    if(row_or_column){
        if(cells->size() > 1){
        for(int j=0; j<width; j++){
            int ref = (*cells)[0][j];
            bool same = true;
            for(int i=1; i<cells->size(); i++){
                if((*cells)[i][j] != ref){
                    same = false;
                    break;
                }
            }
            if(same && diagram[index][j] == 0){
                diagram[index][j] = ref;
                changed = true;
            }
        }
        }
        else if(cells->size() == 1){
            for(int j=0; j<width; j++){
                if(diagram[index][j] == 0){
                    diagram[index][j] = (*cells)[0][j];
                    changed = true;
                }
            }
        }
    }
        else{
            if(cells->size() > 1){
            for(int j=0; j<width; j++){
                int ref = (*cells)[0][j];
                bool same = true;
                for(int i=1; i<cells->size(); i++){
                    if((*cells)[i][j] != ref){
                        same = false;
                        break;
                    }
                }
                if(same && diagram[j][index] == 0){
                    diagram[j][index] = ref;
                    changed = true;
                }
            }
            }
            else if(cells->size() == 1){
                for(int j=0; j<width; j++){
                    if(diagram[j][index] == 0){
                        diagram[j][index] = (*cells)[0][j];
                        changed = true;
                    }
                }
            }

        }
        return changed;
}

int **guess_diagram(vector<int> *cells, int index, bool row_or_column, int m, int n, int **root){
    int **guess = new int *[m];
    for(int i=0; i<m; i++)
        guess[i] = new int[n];
    if(row_or_column){
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(i == index && root[i][j] == 0)
                guess[i][j] = (*cells)[j];
            else
                guess[i][j] = root[i][j];
        }
    }
    }
    else{
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(j == index && root[i][j] == 0)
                    guess[i][j] = (*cells)[j];
                else
                    guess[i][j] = root[i][j];
            }
        }
    }
    return guess;
}

int main(){
    int m, n;
    cin>>m>>n;
    int **diagram = new int *[m];
    for(int i=0; i<m; i++)
        diagram[i] = new int[n];
    
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            diagram[i][j] = 0;
        }
    }
    vector<int> *row = new vector<int>[m];
    vector<int> *column = new vector<int>[n];
 // **********INPUT CLUES*****************
    int temp;
    for(int i=0; i<m; i++){
            while(cin>>temp){
            row[i].push_back(temp);
            if(getchar() == '\n')
                break;
        }
    }
    for(int i=0; i<n; i++){
            while(cin>>temp){
            column[i].push_back(temp);
            if(getchar() == '\n')
                break;
        }
    }
    // **********FIND ALL POSSIBILITIES*************************
    vector< vector<int> > *cells = new vector< vector<int> > [m+n];
    for(int i=0; i<m; i++){
        cells[i].reserve(20);
        possibilities((cells+i), n, (row+i));
    }
    for(int i=0; i<n; i++){
        cells[m+i].reserve(20);
        possibilities((cells+m+i), m, (column+i));
    }
    // *********FILL DIAGRAM******************
    bool modified;
    do{
        modified = false;
        for(int i=0; i<n; i++){
            bool changed;
            changed = confirm((cells+m+i), i, 0, m, diagram);
            if(changed == true)
                modified = true;
        }
        for(int i=0; i<m; i++)
            eliminate((cells+i), i, 1, n, diagram);

        for(int i=0; i<n; i++)
            eliminate((cells+m+i), i, 0, m, diagram);

                for(int i=0; i<m; i++){
            bool changed;
            changed = confirm((cells+i), i, 1, n, diagram);
            if(changed == true)
                modified = true;
        }
    }
    while(modified);

    bool filled = true;
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(diagram[i][j] == 0){
                filled = false;
                break;
            }
        if(!filled)
            break;
        }
    }
   // *************DFS**********************
    if(!filled){
    vector<int **> tree;
    vector<vector< vector<int> > *> clues;
    vector< vector<int> > *temp_cells1 = new vector< vector<int> >[m+n];
    tree.push_back(diagram);
    for(int i=0; i<m+n; i++)
        temp_cells1[i] = cells[i];
    clues.push_back(temp_cells1);
    
    while(tree.size() != 0){
        int **root = tree.back();
        vector< vector<int> > *temp_cells2 = clues.back();
        int k;
        tree.erase(tree.end()-1);
        clues.erase(clues.end()-1);
        for(int i=0; i<m; i++){
            if(temp_cells2[i].size() > 1){
                k = i;
                break;
            }
         }
        bool filled2;
            for(int l=0; l<temp_cells2[k].size(); l++){
                int **guess = guess_diagram(&(temp_cells2[k][l]), k, 1, m, n, root);
                vector< vector<int> > *temp_cells3 = new vector< vector<int> >[m+n];
                for(int i=0; i<m+n; i++)
                    temp_cells3[i] = temp_cells2[i];
                bool modified2 = true;
                while(modified2){
                    modified2 = false;
                    for(int i=0; i<n; i++)
                        eliminate((temp_cells3+m+i), i, 0, m, guess);
                    for(int i=0; i<n; i++){
                        bool changed;
                        changed = confirm((temp_cells3+m+i), i, 0, m, guess);
                        if(changed)
                            modified2 = true;
                    }
                    for(int i=0; i<m ; i++)
                        eliminate((temp_cells3+i), i, 1, n, guess);
                    for(int i=0; i<m ; i++){
                        bool changed;
                        changed = confirm((temp_cells3+i), i, 1, n, guess);
                        if(changed)
                            modified2 = true;
                    }
                }
               
                bool dead = false;
                for(int i=0; i<m+n; i++){
                    if(temp_cells3[i].size() == 0){
                        dead = true;
                        filled2 = false;
                        break;
                    }
                }
                if(!dead){
                    tree.push_back(guess);
                    clues.push_back(temp_cells3);
                    filled2 = true;
                    for(int i=0; i<m; i++){
                        for(int j=0; j<n; j++){
                            if(guess[i][j] == 0){
                                filled2 = false;
                                break;
                            }
                        }
                        if(!filled2)
                            break;
                    }
                }
                if(filled2)
                    break;
                }//end of for possibilities in cells[k]
        
        if(filled2)
            break;
    }  //end of while stack is not empty
    if(tree.size() == 0)
        cout<<"no answer"<<endl;
    else{
    int **answer = tree.back();
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(diagram[i][j] == 0)
                diagram[i][j] = answer[i][j];
        }
    }
    }  //end of else
    } //end of if not filled
 
   // ********PRINT DIAGRAM**************
    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            if(diagram[i][j] == 1)
                cout<<"#";
            else if(diagram[i][j] == -1)
                cout<<".";
            else if(diagram[i][j] == 0)
                cout<<" ";
            else
                cout<<"x";
        }
        cout<<endl;
    }
    delete[] diagram;
    return 0;
}
