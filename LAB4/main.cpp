#include <string>
#include <iostream>
#include <fstream>
#include<sstream>

using namespace std;
 stringstream ss;

static void clear(char s[100], int *n)
{
	char c[100];
	int k = *n;
	*n = 0;
	for(int i = 0; i<k; i++)
	{
		for(int j = 0; j<k; j++)
		{
			if (s[i] ==s[j] and i!=j)
			{
				s[j] = '*';
			}
		}
		if(s[i]!='*')
		{
			c[*n] = s[i];
			*n+=1;
		}
	}
	 for(int i = 0; i<*n; i++)
	 s[i] = c[i];

}

static void remove(string s[100], int *n, int r)
{
	for(int i = r; i<*n; i++)
	{
		s[i] = s[i+1];
	}
	*n-=1;;
}
static void remove_duplicates_y(string s[100],int *n)
{
	for(int i = 0; i<*n; i++)
	{
		for(int j = 0; j<*n; j++)
		{
			if (s[i] == s[j] and i!=j) remove(s,n,i);
		}
	}
}

static void remove_duplicates(string s[100],int *n,int start)
{
	for(int i = start; i<*n; i++)
	{
		for(int j = 0; j<start; j++)
		{
			if (s[i] == s[j] and i!=j) remove(s,n,i);
		}
	}

	for(int i = start; i<*n; i++)
	{
		for(int j = start; j<*n; j++)
		{
			if (s[i] == s[j] and i!=j) remove(s,n,j);
		}
	}
}

static void remove_c(string c[100], char a,int *u)
{
	int pos = *u;
	string str = c[pos];
	for(int i = 2; i<= c[pos].size(); i++)
	{

		if(c[pos][i]==a) { c[pos].erase(i,1); pos++;}
		c[pos] = str;
	}

	for(int i = 2; i<= c[pos].size(); i++)
	{
		if(c[pos][i]==a) { c[pos].erase(i,1);}
	}
	*u = pos;
}

static void read(string s[100], int *n)
{
    string myText, var;
    int i = 0;

    fstream file;
    file.open("input.txt");

    while (getline(file, myText))
	{
	s[i] = myText;
		i++;
		cout<<s[i-1]<<endl;
    }
    file.close();
    *n=i;
}

int main()
{
	string s[100];
	char empty;
	int n;

		cout<<"--------------------------------------------------------"<<endl;
		cout<<"Given Context Free Gramar"<<endl;;
			cout<<"--------------------------------------------------------"<<endl<<endl;
    read(s,&n);

    	cout<<endl<<"--------------------------------------------------------"<<endl;

    //#1.remove e productions
	for(int i = 0; i<n; i++)
	{
		if (s[i][2] == 'e')
		{
			empty = s[i][0];
			remove(s,&n,i);
		}
	}
	int k = n;
	for(int i = 0; i<k; i++)
	{
		s[n] = s[i];
		remove_c(s,empty,&n);
		n++;
	}
	remove_duplicates(s,&n,k);

	cout<<"1.Removed e productions:"<<endl;
		cout<<"--------------------------------------------------------"<<endl<<endl;
	for(int i = 0; i<n; i++)
	{
		cout<<s[i]<<endl;
	}
	cout<<endl<<"--------------------------------------------------------"<<endl;

	//#2.remove renamings

	char ren[100][2];
	int o = 0;

	for(int i = 0; i<n; i++)
	{
		if (s[i].size() == 3 and s[i][0]>='A' and s[i][0]<='Z' and s[i][2]>='A' and s[i][2]<='Z')
		{
			ren[o][0] = s[i][0];
			ren[o][1] = s[i][2];
			o++;
			remove(s,&n,i);
		}
	}
	int k1 = n;
	for(int j = 0; j<o; j++)
	for(int i = 0; i<k1; i++)
	{
		if (s[i][0]==ren[j][1])
		{
			s[n] = s[i];
			s[n][0] = ren[j][0];
			n++;
		}
	}
	k1 = n;

	cout<<"2.Removed renamings:"<<endl;
		cout<<"--------------------------------------------------------"<<endl<<endl;
	for(int i = 0; i<n; i++)
	{
		cout<<s[i]<<endl;
	}
	cout<<endl<<"--------------------------------------------------------"<<endl;

	//#3.remove nonproductive symbols


	//All symbols
	char all_sym[100];
	int q = 0;

	for(int i =0; i<k; i++)
	{
		all_sym[q] = s[i][0];
		q++;
	}
	clear(all_sym,&q);

	//Productive symbols
	char p_sym[100];
	int t = 0;

	for(int i =k; i<k1; i++)
	{
		p_sym[t] = s[i][0];
		t++;
	}
	clear(p_sym,&t);

	//Nonproductive symbols

	int count =0;
	char n_sym[100];
	int p = 0;
	for(int i =0; i<q; i++)
	{
		for(int j =0; j<t; j++)
			{
				if (p_sym[j]==all_sym[i]) count = 1;
			}
		if (count == 0)
			{
				n_sym[p] = all_sym[i];
				p++;
			}
			count = 0;
	}

	//remove from grammar

	for(int j =0; j<p; j++)
	for(int i =0; i<k1; i++)
	{
		if (s[i][0] ==n_sym[j] ){ remove(s,&n,i);}
		for(int y = 2; y<s[i].size();y++)
		if (s[i][y]==n_sym[j])
		{ remove(s,&n,i);}
	}

	cout<<"3.Removed nonproductive symbols:"<<endl;
		cout<<"--------------------------------------------------------"<<endl<<endl;
	for(int i = 0; i<n; i++)
	{
		cout<<s[i]<<endl;
	}
	cout<<endl<<"--------------------------------------------------------"<<endl;

	//#4. remove innaccesible points

	char in_points[100];
	int f = 0;
		for(int j =0; j<t; j++)
		{

			for(int i =0; i<k1; i++)
			{
				for(int y = 2; y<s[i].size();y++)
				if (s[i][y]==p_sym[j]) count = 1;
			}
			if (count == 0)
			{
				in_points[f] = p_sym[j];
				f++;
			}
			count = 0;

		}

	for(int j =0; j<f; j++)
	for(int i =0; i<n; i++)
	{
		if (s[i][0] ==in_points[j] )
		{	remove(s,&n,i); i--;}
	}

		cout<<"4.Removed innaccesible points:"<<endl;
			cout<<"--------------------------------------------------------"<<endl<<endl;
	for(int i = 0; i<n; i++)
	{
		cout<<s[i]<<endl;
	}
	cout<<endl<<"--------------------------------------------------------"<<endl;

	//#5. CFG to CNF
	string y[100];
	int m =0;
	for(int i = 0; i<n; i++)
	{
		if (s[i].size()-2 > 2) { y[m] = s[i]; y[m].erase(0,3); m++;}
		if ( y[m-1].size() > 2) {y[m] = y[m-1]; y[m].erase(0,1); m++;}
	}
		remove_duplicates_y(y,&m);
			char num_char[100];
		string cut;
		string sequence;
		for(int i = 0; i<n; i++)
		{
			cut = s[i];
			cut.erase(0,3);
			for(int j = 0; j<m; j++)
			{
				if (cut == y[j])
				{
					sequence = s[i];
					sequence.erase(3,sequence.size());
					s[i][3] = 'Y';
					sprintf(num_char, "%d", j+1);
					s[i][4] = num_char[0];
						s[i] = sequence + "Y"+num_char[0];
				}
			}
		}
			string x[100];
			int w = 0;
			for(int i = 0; i<n; i++)
		{
			if((s[i].size()-2==2 or s[i].size()-2==1) and s[i][2]>='a' and s[i][2]<='z')
			{
				x[w] = s[i][2];
				w++;
			}
		}
			remove_duplicates_y(x,&w);
			remove_duplicates_y(x,&w);
			for(int i = 0; i<n; i++)
		{
			for(int j = 0; j<w; j++)
			{
				if ((x[j][0] == s[i][2] or x[j][0] == s[i][3]) and s[i].size()-2>1)
				{
					sequence = s[i];
					sequence.erase(2,1);
						sprintf(num_char, "%d", j+1);
					sequence.insert(2,"X");
					sequence.insert(3,num_char);
					s[i] = sequence;
				}
			}
		}

		for(int i = 0; i<m; i++)
		{
			if (y[i].size() == 3)
			{
				y[i][1] = 'Y';
				sprintf(num_char, "%d", i+2);
				y[i][2] = num_char[0];
			}
		}
		for(int i = 0; i<m; i++)

		{
			for(int j =0; j<w; j++)
			if (y[i][0] == x[j][0])
			{
				y[i].erase(0,1);
				sprintf(num_char, "%d", j+1);
					y[i].insert(0,"X");
					y[i].insert(1,num_char);
			}
			else
			if (y[i][1] == x[j][0])
			{
				y[i].erase(1,1);
				sprintf(num_char, "%d", j+1);
					y[i].insert(1,"X");
					y[i].insert(2,num_char);
			}
		}

			for(int i = n; i<n+w; i++)
		{
			sprintf(num_char, "%d", i-n+1);
			s[i] = x[i-n];
			s[i].insert(0,"X");
			s[i].insert(1,num_char);
			s[i].insert(2,">");
		}
		n+=w;


			for(int i = n; i<n+m; i++)
		{
			sprintf(num_char, "%d", i-n+1);
			s[i] = y[i-n];
			s[i].insert(0,"Y");
			s[i].insert(1,num_char);
			s[i].insert(2,">");
		}
		n+=m;
	cout<<"5.Converted:"<<endl;
		cout<<"--------------------------------------------------------"<<endl<<endl;
	for(int i = 0; i<n; i++)
	{
		cout<<s[i]<<endl;
	}
	cout<<endl<<"--------------------------------------------------------"<<endl;
}
