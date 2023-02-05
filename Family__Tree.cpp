#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

//baray negahdari zaman
struct date
{
    int day ;
    int month;
    int year;
};

// baray negahdari etelate har shakhs
struct person
{
    int _id ; // Code Melli
    string _Fname; //Nam
    string _Lname; // Nam Khanevadegi
    date _birth; // Tarikh tavalod
    date _death; // Tarikh Fot
    bool _gender; // Jensiat
    vector <int> _spouse; // Code melli Hamsaran
    vector <int> _children; // Code melli Farzandan
    int _father ; // Code melli Pedar
    int _mother ; // Code melli Madar

    string get_name() // Tabeii ke nam va nam khanevadegi shakhs ra barmigardanad
    {
        return _Fname + _Lname ;
    }
};

class family_tree
{
    private:
        vector <person> family_members;
        int size = 0 ;
    public:
        void print_all_members();
        void add_new_person(person Person);
        int Counting_the_number_of_grandchildren(int id);
        person have_most_children();
        void print_all_coupels_without_relationshilp();
        vector<person> get_person_that_have_this_relation( int id , string relation);
        string check_have_relationship(int id1 , int id2);
        person get_person_by_id(int id);
        vector<int> get_id_by_name(string name);
        int get_mother(int id);
        int get_father(int id);
        vector<int> get_sister(int id);
        vector<int> get_brother(int id);
        vector<int> get_havoo(int id);
        vector<int> get_jari(int id);
        vector<int> get_bajenagh(int id);
        vector<int> get_spouse(int id);
        vector<int> get_children(int id);
        bool get_gender(int id)
        {
            for( int i = 0 ; i < size ; i++)
            {
                if ( family_members[i]._id == id)
                {
                    return family_members[i]._gender;
                }
            }
            return false;
        }
};

void family_tree :: print_all_members()
{
    for ( int i = 0 ; i < size ; i++ )
    {
        cout << family_members[i].get_name();
        for( int j = 0 ; j < family_members[i]._spouse.size() ; j++ )
        {
            cout << family_members[i]._spouse[j];
        }
        for( int j = 0 ; j < family_members[i]._children.size() ; j++ )
        {
            cout << family_members[i]._children[j];
        }
    }
}
// Afzoodan Ozve Jadid
void family_tree :: add_new_person(person Person)
{
    family_members.push_back(Person); // Moshakhasat Fard ra ke daroon moteghayer person gharar darad be entehay vector ezafeh mikonad
    size += 1; // be motagheyer size ke tedad azay derakht ra neshan midahad yeki ezafeh mikonad
};

// Shakhsi ra ke id khasteh shode ra dard peyda mikonad
person family_tree :: get_person_by_id( int id )
{
    person Person ;
    for ( int i = 0 ; i < size ; i++)
    {
        if ( family_members[i]._id == id )
        {
            return family_members[i];
        }
    }
    return Person; 
}


vector<int> family_tree :: get_id_by_name(string name)
{
    vector<int> result;
    for(int i = 0 ; i < size ; i++)
    {
        if( family_members[i]._Fname == name )
        {
            result.push_back(family_members[i]._id);
        }
    }
    return result;
}

bool is_visited(vector<int> visited,int id)
{
    for(int i = 0 ; i < visited.size() ; i++)
    {
        if( id == visited[i] )
        {
            return true;
        }
    }
    return false;
}
// Shomaresh tedad navadegan 
int family_tree :: Counting_the_number_of_grandchildren(int id)
{
    int counter = 0 ;
    vector<int> visited;
    stack<int> stack;
    stack.push(id);
    visited.push_back(id);
    while (!stack.empty())
    {
        int u = stack.top();
        stack.pop();
        counter++;
        vector<int> child = get_children(u);
        for( int i = 0 ; i < child.size() ; i++ )
        {
            if (!is_visited(visited,child[i]))
            {
                stack.push(child[i]);
                visited.push_back(child[i]);
            }
        }
    }
    return counter;
};

// Peyda Kardan Kasi ke bishtarin Farzand ra darad
person family_tree :: have_most_children()
{
    int max = -1;
    person have_max_childs ;
    int temp;
    for(int i = 0 ; i < size ; i++)
    {
        temp = Counting_the_number_of_grandchildren(family_members[i]._id);
        if (temp > max)
        {
            max = temp;
            have_max_childs = family_members[i];
        }
    }
    return have_max_childs;
};

int family_tree :: get_father( int id )
{
    person Person = get_person_by_id(id);
    return Person._father;
};

int family_tree :: get_mother( int id )
{
    person Person = get_person_by_id(id);
    return Person._mother;
};

vector<int> family_tree :: get_sister(int id)
{
    vector<int> result;
    int father = get_father(id);
    vector<int> children = get_children(father);
    for ( int i = 0 ; i < children.size() ; i++)
    {
        if ( get_gender(children[i]) == 0 and children[i] != id )
        {
            result.push_back(children[i]);
        }
    }
    return result;
};

vector<int> family_tree :: get_brother( int id )
{
    vector<int> result;
    int father = get_father(id);
    vector<int> children = get_children(father);
    for ( int i = 0 ; i < children.size() ; i++)
    {
        if ( get_gender(children[i]) == 1 and children[i] != id )
        {
            result.push_back(children[i]);
        }
    }
    return result;
};

vector<int> family_tree :: get_havoo(int id)
{
    vector<int> result;
    vector<int> spouse = get_spouse(id);
    vector<int> havoo;
    for ( int i = 0 ; i < spouse.size() ; i++ )
    {
        havoo = get_spouse(spouse[i]);
        for ( int j = 0 ; j < havoo.size() ; j++ )
        {
            if ( havoo[j] != id )
            {
                result.push_back(havoo[j]);
            }
        }
    }
    return result;
};

vector<int> family_tree :: get_bajenagh( int id )
{
    vector<int> result;
    vector<int> spouse = get_spouse(id);
    for( int i = 0 ; i < spouse.size() ; i++ )
    {
        vector<int> sister = get_sister(spouse[i]);
        for( int j = 0 ; j < sister.size() ; j++ )
        {
            vector<int> bajenagh = get_spouse(sister[j]);
            for( int k = 0 ; k < bajenagh.size() ; k++ )
            {
                result.push_back(bajenagh[k]);
            }
        }
    }
    return result;
};

vector<int> family_tree :: get_jari( int id )
{
    vector<int> result;
    vector<int> spouse = get_spouse(id);
    for( int i = 0 ; i < spouse.size() ; i++ )
    {
        vector<int> brother = get_brother(spouse[i]);
        for( int j = 0 ; j < brother.size() ; j++ )
        {
            vector<int> jari = get_spouse(brother[j]);
            for( int k = 0 ; k < jari.size() ; k++ )
            {
                result.push_back(jari[k]);
            }
        }
    }
    return result;
};

vector<int> family_tree :: get_children(int id)
{
    person Person = get_person_by_id(id);
    return Person._children;
};

vector<int> family_tree :: get_spouse(int id)
{
    person Person = get_person_by_id(id);
    
    return Person._spouse;
}

string family_tree :: check_have_relationship( int id1 , int id2 )
{
    string result = "";
    vector<int> temp ;
    vector <int> childs;
    vector<int> spouse;
    int Temp;

    // Hamsar 
    spouse = get_spouse(id2);
    if ( is_visited(spouse,id1) == true )
    {
        if( get_gender(id1) == 0 )
        {
            result = "Zan";
        }
        else if ( get_gender(id1) == 1 )
        {
            result = "Shoohar";
        }
    }

    // Farzand
    childs = get_children(id2 );
    if ( is_visited(childs,id1) == true )
    {
        if( get_gender(id1) == 0 )
        {
            result += "Dokhtar";
            return result;
        }
        else if ( get_gender(id1) == 1 )
        {
            result += "Pesar";
            return result;
        }
    }
    
    // Pedar
    if ( get_father(id2) == id1 )
    {
        result += "Pedar" ;
        return result;
    }

    // Madar
    if( get_mother(id2) == id1 )
    {
        result += "Madar";
        return result;
    }

    //Khahar
    temp = get_sister(id2);
    if ( is_visited(temp,id1) == true )
    {
        result += "Khahar";
        return result;
    }

    for ( int i = 0 ; i < temp.size() ; i++ )
    {
        childs = get_children(temp[i]);
        if ( is_visited(childs,id1) == true)
        {
            if ( get_gender(id1) == 0 )
            {
                result += " Dokhtar Khahar";
                return result;
            }
            else 
            {
                result += " Pesar Khahar";
                return result;
            }
        }
        spouse = get_spouse(temp[i]);
        if ( is_visited(spouse,id1) == true )
        {
            result += " Shoohar Khahar";
            return result;
        }
    }

    // Baradar
    temp = get_brother(id2);
    if ( is_visited(temp,id1) == true )
    {
        result += " Baradar";
        return result;
    }

    for ( int i = 0 ; i < temp.size() ; i++ )
    {
        childs = get_children(temp[i]);
        if ( is_visited(childs,id1) == true)
        {
            if ( get_gender(id1) == 0 )
            {
                result += " Dokhtar Baradar";
                return result;
            }
            else 
            {
                result += " Pesar Baradar";
                return result;
            }
        }
        spouse = get_spouse(temp[i]);
        if ( is_visited(spouse,id1) == true )
        {
            result += " Zan Baradar";
        }
    }

    //PedarBozorg
    if(get_father(get_father(id2)) == id1 || get_father(get_mother(id2)) == id1 )
    {
        result += " Pedar Bozorg";
        return result;
    }

    // MadarBozorg
    if(get_mother(get_father(id2)) == id1 || get_mother(get_mother(id2)) == id1)
    {
        result += " Mothar Bozorg";
        return result;

    }

    // amme
    temp = get_sister(get_father(id2));
    if ( is_visited(temp,id1) == true )
    {
        result += " Amme";
        return result;
    }

    for( int i = 0 ; i < temp.size() ; i++ )
    {
        childs = get_children(temp[i]);
        if ( is_visited(childs,id1) == true )
        {
            if ( get_gender( id1) == 0 )
            {
                result += " Dokhtar Amme";
                return result;
            }
            else 
            {
                result += " Pesar Amme";
                return result;
            }
        }

        spouse = get_spouse(temp[i]);
        if ( is_visited(spouse,id1) == true)
        {
            result += " Shoohar Amme";
            return result;
        }
    }

    // Khale
    temp = get_sister(get_mother(id2));
    if ( is_visited(temp,id1) == true )
    {
        result += " Khaleh";
        return result;
    }

    for( int i = 0 ; i < temp.size() ; i++ )
    {
        childs = get_children(temp[i]);
        if ( is_visited(childs,id1) == true )
        {
            if ( get_gender( id1) == 0 )
            {
                result += " Dokhtar Khale";
                return result;
            }
            else 
            {
                result += " Pesar Khale";
                return result;
            }
        }

        spouse = get_spouse(temp[i]);
        if ( is_visited(spouse,id1) == true)
        {
            result += " Shoohar Khale";
            return result;
        }
    }

    // Daii
    temp = get_brother(get_mother(id2));
    if ( is_visited(temp,id1) == true )
    {
        result += " Daii";
        return result;
    }

    for( int i = 0 ; i < temp.size() ; i++ )
    {
        childs = get_children(temp[i]);
        if ( is_visited(childs,id1) == true )
        {
            if ( get_gender( id1) == 0 )
            {
                result += " Dokhtar Daii";
                return result;
            }
            else 
            {
                result += " Pesar Daii";
                return result;
            }
        }

        spouse = get_spouse(temp[i]);
        if ( is_visited(spouse,id1) == true)
        {
            result += " Zan Daii";
            return result;
        }
    }

    // Amo
    temp = get_brother(get_father(id2));
    if ( is_visited(temp,id1) == true )
    {
        result += " Amo";
        return result;
    }

    for( int i = 0 ; i < temp.size() ; i++ )
    {
        childs = get_children(temp[i]);
        if ( is_visited(childs,id1) == true )
        {
            if ( get_gender( id1) == 0 )
            {
                result += " Dokhtar Amo";
                return result;
            }
            else 
            {
                result += " Pesar Amo";
                return result;
            }
        }

        spouse = get_spouse(temp[i]);
        if ( is_visited(spouse,id1) == true)
        {
            result += " Zan Amo";
            return result;
        }
    }

    // Bajenagh
    temp = get_bajenagh(id2);
    if ( is_visited(temp,id1) == true )
    {
        result += " Bajenagh";
        return result;
    }

    // Jari
    temp = get_jari(id2);
    if ( is_visited(temp,id1) == true )
    {
        result += " jari";
        return result;
    }

    // Havoo
    temp = get_havoo(id2);
    if ( is_visited(temp,id1) == true )
    {
        result += " Havoo";
        return result;
    }

    // Khahar Shoohar || Khahar Zan
    spouse = get_spouse(id2);
    for ( int i = 0 ; i < spouse.size() ; i++ )
    {
        temp = get_sister(spouse[i]);
        if( is_visited(temp,id1) == true )
        {
            if ( get_gender(id2) == 0 )
            {
                result += " Khahar Shoohar";
                return result;
            }
            else
            {
                result += " Khahar Zan";
                return result;
            }
        }
    }

    // Baradar shoohar || Baradar Zan
    for ( int i = 0 ; i < spouse.size() ; i++ )
    {
        temp = get_brother(spouse[i]);
        if( is_visited(temp,id1) == true )
        {
            if ( get_gender(id2) == 0 )
            {
                result += " Khahar Shoohar";
                return result;
            }
            else
            {
                result += " Khahar Zan";
                return result;
            }
        }
    }

    // Madar Zan || Madar Shoohar
    for( int i = 0 ; i < spouse.size() ; i++)
    {
        Temp = get_mother(spouse[i]);
        if ( Temp == id1)
        {
            if( get_gender(id2) == 0 )
            {
                result += " Madar Shoohar";
                return result;
            }
            result += " Madar Zan";
            return result;
        }        
    }

    // Pedar Zan || Pedar Shoohar
    for( int i = 0 ; i < spouse.size() ; i++)
    {
        Temp = get_father(spouse[i]);
        if ( Temp == id1)
        {
            if( get_gender(id2) == 0 )
            {
                result +=  " Pedar Shoohar";
            }
            result += " Pedar Zan";
            return result;
        }        
    }

    // Aroos || Damad
    childs = get_children(id2);
    for ( int i = 0 ; i < childs.size() ; i++)
    {
        spouse = get_spouse(childs[i]);
        if(is_visited(spouse,id1) == true)
        {
            if ( get_gender(id1) == 0 )
            {
                result += " Aroos";
                return result;
            }
            else
            {
                result += " Damad";
                return result;
            }
        }
        
        temp = get_children(childs[i]);
        if ( is_visited(temp,id1) == true )
        {
            result += " Nave";
            return result;
        }
    }
    
    return result;
};

void family_tree :: print_all_coupels_without_relationshilp()
{
    vector<int> array;
    vector<int> temp;
    person Temp;
    for( int i = 0 ; i < size ; i++ )
    {
        array.push_back(family_members[i]._id);
        temp = family_members[i]._spouse;
        for( int j = 0 ; j < temp.size() ; j++ )
        {
            if( is_visited(array,temp[j]) == false)
            {
                string T = check_have_relationship(temp[j],family_members[i]._id);
                if ( T == "Zan" || T == "Shoohar")
                {
                    Temp = get_person_by_id(temp[j]);
                    cout << Temp.get_name() << " And " << family_members[i].get_name() <<"\n";
                }
            }
        }
    }
};

vector<person> family_tree :: get_person_that_have_this_relation( int id , string relation)
{
    vector<int> Temp;
    vector<person> result;
    int temp ;
    if ( relation == "Hamsar")
    {
        Temp = get_spouse(id);
        for(int i = 0 ; i < Temp.size() ; i++ )
        {
            result.push_back(get_person_by_id(Temp[i]));
        }
        return result;
    }
    if(relation == "Farzand")
    {
        Temp = get_children(id);
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            result.push_back(get_person_by_id(Temp[i]));
        }
        return result;
    }
    if (relation == "Pedar")
    {
        temp = get_father(id);
        result.push_back(get_person_by_id(temp));
        return result;
    }
    if (relation == "Madar")
    {
        temp = get_mother(id);
        result.push_back(get_person_by_id(temp));
        return result;
    }
    if ( relation == "Khahar")
    {
        Temp = get_sister(id);
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            result.push_back(get_person_by_id(Temp[i]));
        }
        return result;
    }
    if( relation == "Baradar")
    {
        Temp = get_brother(id);
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            result.push_back(get_person_by_id(Temp[i]));
        }
        return result;
    }
    if( relation == "Khale" )
    {
        Temp = get_sister(get_mother(id));
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            result.push_back(get_person_by_id(Temp[i]));
        }
        return result;
    }
    if( relation == "Daii")
    {
        Temp = get_brother(get_mother(id));
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            result.push_back(get_person_by_id(Temp[i]));
        }
        return result;
    }
    if( relation == "Amo")
    {
        Temp = get_brother(get_father(id));
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            result.push_back(get_person_by_id(Temp[i]));
        }
        return result;
    }
    if( relation == "Amme")
    {
        Temp = get_sister(get_father(id));
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            result.push_back(get_person_by_id(Temp[i]));
        }
        return result;
    }
    if ( relation == "Jari")
    {
        Temp = get_jari(id);
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            result.push_back(get_person_by_id(Temp[i]));
        }
        return result;
    }
    if (relation == "Havoo")
    {
        Temp = get_havoo(id);
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            result.push_back(get_person_by_id(Temp[i]));
        }
        return result;
    }
    if ( relation == "Bajenagh")
    {
        Temp = get_bajenagh(id);
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            result.push_back(get_person_by_id(Temp[i]));
        }
        return result;
    }
    if ( relation == "Pedar Bozorg")
    {
        temp = get_father(id);
        result.push_back(get_person_by_id(get_father(temp)));
        temp = get_mother(id);
        result.push_back(get_person_by_id(get_father(temp)));
        return result;
    }
    if ( relation == "Madar Bozorg")
    {
        temp = get_father(id);
        result.push_back(get_person_by_id(get_mother(temp)));
        temp = get_mother(id);
        result.push_back(get_person_by_id(get_father(temp)));
        return result;
    }
    if ( relation == "Pesar Khale")
    {
        Temp = get_sister(get_mother(id));
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_children(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                if ( get_gender(temp[j]) == 1)
                {
                    result.push_back(get_person_by_id(temp[j]));
                }
                
            } 
        }
        return result;
    }
    if( relation == "Dokhtar_Khale")
    {
        Temp = get_sister(get_mother(id));
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_children(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                if ( get_gender(temp[j]) == 0)
                {
                    result.push_back(get_person_by_id(temp[j]));
                }
                
            } 
        }
        return result;
    }
    if ( relation == "Pesar Amo")
    {
        Temp = get_brother(get_father(id));
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_children(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                if ( get_gender(temp[j]) == 1)
                {
                    result.push_back(get_person_by_id(temp[j]));
                }
                
            } 
        }
        return result;
    }
    if ( relation == "Dokhtar Amo")
    {
        Temp = get_brother(get_father(id));
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_children(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                if ( get_gender(temp[j]) == 0 )
                {
                    result.push_back(get_person_by_id(temp[j]));
                }
                
            } 
        }
        return result;
    }
    if ( relation == "Pesar Amme")
    {
        Temp = get_sister(get_father(id));
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_children(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                if ( get_gender(temp[j]) == 1)
                {
                    result.push_back(get_person_by_id(temp[j]));
                }
                
            } 
        }
        return result;
    }
    if ( relation == "Dokhtar Amme")
    {
        Temp = get_sister(get_father(id));
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_children(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                if ( get_gender(temp[j]) == 0 )
                {
                    result.push_back(get_person_by_id(temp[j]));
                }
                
            } 
        }
        return result;
    }
    if ( relation == "Dokhtar Daii")
    {
        Temp = get_brother(get_mother(id));
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_children(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                if ( get_gender(temp[j]) == 0)
                {
                    result.push_back(get_person_by_id(temp[j]));
                }
                
            } 
        }
        return result;
    }
    if ( relation == "Pesar Daii")
    {
        Temp = get_brother(get_mother(id));
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_children(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                if ( get_gender(temp[j]) == 1)
                {
                    result.push_back(get_person_by_id(temp[j]));
                }
                
            } 
        }
        return result;
    }
    if ( relation == " Zan Baradar ")
    {
        Temp = get_brother(id);
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_spouse(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                result.push_back(get_person_by_id(temp[j]));
            } 
        }
        return result;
    }
    if ( relation == " Shoohar Khahar ")
    {
        Temp = get_brother(id);
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_spouse(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                result.push_back(get_person_by_id(temp[j]));
            } 
        }
        return result;
    }
    if ( relation == "Khahar Zade")
    {
        Temp = get_sister(id);
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_children(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                result.push_back(get_person_by_id(temp[j]));
            } 
        }
        return result;
    }
    if ( relation == "Baradar Zade")
    {
        Temp = get_brother(id);
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_children(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                result.push_back(get_person_by_id(temp[j]));
            } 
        }
        return result;
    }
    if ( relation == "Shoohar Amme")
    {
        Temp = get_sister(get_father(id));
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_spouse(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                result.push_back(get_person_by_id(temp[j]));
            } 
        }
        return result;
    }
    if ( relation == "Shoohar Khale")
    {
        Temp = get_sister(get_mother(id));
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_spouse(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                result.push_back(get_person_by_id(temp[j]));
            } 
        }
        return result;
    }
    if ( relation == "Zan Amo")
    {
        Temp = get_brother(get_father(id));
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_spouse(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                result.push_back(get_person_by_id(temp[j]));
            } 
        }
        return result;
    }
    if ( relation == "Zan Daii")
    {
        Temp = get_brother(get_mother(id));
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_spouse(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                result.push_back(get_person_by_id(temp[j]));
            } 
        }
        return result;
    }
    if ( relation == "Khahr Shoohar" || relation == "Khahar Zan")
    {
        Temp = get_spouse(id);
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_sister(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                result.push_back(get_person_by_id(temp[j]));
            } 
        }
        return result;
    }
    if ( relation == "Baradar Shoohar" || relation == "Baradar Zan")
    {
        Temp = get_spouse(id);
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_brother(Temp[i]);
            for( int j = 0 ; j < temp.size() ; j++)
            {
                result.push_back(get_person_by_id(temp[j]));
            } 
        }
        return result;
    }
    if ( relation == "Madar Zan" || relation == "Madar Shoohar")
    {
        Temp = get_spouse(id);
        int temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_mother(Temp[i]);
            result.push_back(get_person_by_id(temp));
        }
        return result;
    }
    if ( relation == "Pedar Zan" || relation == "Pedar Shoohar")
    {
        Temp = get_spouse(id);
        int temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_father(Temp[i]);
            result.push_back(get_person_by_id(temp));
        }
        return result;
    }
    if ( relation == "Damad")
    {
        Temp = get_children(id);
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            if ( get_gender(Temp[i]) == 0)
            {
                temp = get_spouse(Temp[i]);
                for ( int j = 0 ; j < temp.size() ; j++)
                {
                    result.push_back(get_person_by_id(temp[j]));
                }
            }
            
        }
        return result;
    }
    if ( relation == "Aroos")
    {
        Temp = get_children(id);
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            if ( get_gender(Temp[i]) == 1 )
            {
                temp = get_spouse(Temp[i]);
                for ( int j = 0 ; j < temp.size() ; j++)
                {
                    result.push_back(get_person_by_id(temp[j]));
                }
            }
            
        }
        return result;
    }
    if ( relation == "Nave")
    {
        Temp = get_children(id);
        vector<int> temp ;
        for( int i = 0 ; i < Temp.size() ; i++)
        {
            temp = get_children(Temp[i]);
            for ( int j = 0 ; j < temp.size() ; j++)
            {
                result.push_back(get_person_by_id(temp[j]));
            }
        }
        return result;
    }
    return result;
};



int main()
{
    string temp ;
    int Temp , n;
    bool gen ;
    vector<person> persons;
    family_tree FT ;
    cout << "Entekhab konid: \n";
    int choice = 0 ;
    int k = 0 ;
    while ( choice != 6 )
    {

        cout << " 1 : Vared kardan ozve jadid \n 2 : Zon va shooharani ke nesbat family nadarand \n 3 : Peyda kardan tammam afrad ba yek nesbat \n 4 : Fardi ke bishtarin nave ra darad \n 5 : Peyda kardan nesbat do fard ba ham  \n 6 : khoroj \n";
        cout << " Entekhab Shoma : " ;
        cin >> choice ;
        if ( choice == 1 )
        {
            int ch = 0 ;
            while(ch == 0 ){
                person person;
                cout << "Nam : ";
                cin >>temp ;
                person._Fname = temp;
                cout << "Nam Khanevadegi : ";
                cin >> temp;
                person._Lname = temp;
                cout << "Kode Melli : ";
                cin >> Temp ;
                person._id = Temp;
                cout << "Tarikh Tavalod : \n";
                cout << "Rooz : ";
                cin>> Temp ;
                person._birth.day = Temp;
                cout << "Mah : ";
                cin >> Temp;
                person._birth.month = Temp;
                cout << "Sal : ";
                cin >> Temp ;
                person._birth.day = Temp;
                cout << "Tarikh Marg (Agar Fard Zendeh ast baray rooz , mah va sal meghdar 0 ra vared konid) :\n";
                cout << "Rooz : ";
                cin>> Temp ;
                person._death.day = Temp;
                cout << "Mah : ";
                cin >> Temp;
                person._death.month = Temp;
                cout << "Sal : ";
                cin >> Temp ;
                person._death.day = Temp;
                cout << "Jensiat ( 0 : Zan , 1 : Mard ) :";
                cin >> gen;
                person._gender = gen;
                cout << "Tedad Hamsaran : ";
                cin >> n ;
                for ( int i = 0 ; i < n ; i++)
                {
                    cout << " Id Hamsar ";
                    cin >> Temp;
                    person._spouse.push_back(Temp);
                }
                cout << "Tedad Farzandan : ";
                cin >> n ;
                for ( int i = 0 ; i < n ; i++)
                {
                    cout << " Id Farzand ";
                    cin >> Temp;
                    person._children.push_back(Temp);
                }
                k++;
                cout << " Id Pedar : ";
                cin >> Temp;
                person._father = Temp;
                cout << " Id Madar : ";
                cin >> Temp;
                person._mother = Temp;

                FT.add_new_person(person);
                cout <<"Agar mikhahid edame dahid 0 va dar gheir in sort meghdar digari ra vared konid : ";
                cin >> ch ;
            }
            FT.print_all_members();
        }
        else if (choice == 2)
        {
            FT.print_all_coupels_without_relationshilp();
        }
        else if ( choice == 3 )
        {
            cout << "Agar Mayel be jostojo ba Esm hastid adad 1 va agar mayel be jostojo ba Kode Melli hastid adad 2 ra vared konid ";
            cin >> n ;
            if ( n == 1 )
            {

                vector<int> temp1 ;
                cout << "Nam MoredNazar ra vared konid : ";
                cin >> temp ;
                temp1 = FT.get_id_by_name(temp);
                cout << "Nesbat madNazar ra ba in format vared konid ( Madar Zan ya Amo ) : ";
                cin >> temp; 
                for ( int i = 0 ; i < temp1.size() ; i++)
                {
                    persons = FT.get_person_that_have_this_relation(temp1[i],temp);
                }

            }
            else if ( n == 2 )
            {
                cout << "Kode Melli MoredNazar ra vared konid : ";
                cin >> Temp ;
                cout << "Nesbat MadNazar ra ba in format vared konid ( Madar Zan ya Amo ) : ";
                cin >> temp ;
                persons = FT.get_person_that_have_this_relation(Temp,temp);
            }

            for ( int i = 0 ; i < persons.size() ; i++)
            {
                cout <<  persons[i].get_name() << "\n";
            }
        }
        else if ( choice == 4 )
        {
            person Person = FT.have_most_children();
            cout << Person.get_name() << " \n ";
        }
        else if ( choice == 5 )
        {
            int id1 , id2 ;
            cout << "Id nafar aval : ";
            cin >> id1 ;
            cout << "Id nafar dovom : ";
            cin >> id2 ;
            cout << FT.check_have_relationship(id1 , id2) << "\n";
        }
        else if ( choice == 6 )
        {
            return 0;
        }
        cout <<"\n\n";
    }
    return 0 ;
}