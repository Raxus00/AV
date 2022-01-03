#include "av.hpp"
//Rasmus Andersen   rasmus.andersen00@gmail.com
//Erik Nordahl  eriknordahl23@gmail.com 


std::vector<std::string> AV::read()
{
    std::ifstream read;
    std::string data;
    std::vector<std::string> datavector;

    read.open("signatures.db");
    if(!read)
    {
        std::cout<<"Could not open file"<<std::endl;
        exit(1);
    }
    else
    {
        while(read>>data)
        {
            datavector.push_back(data);
        }
        read.close();
        return datavector;
    }
}

void AV::treverase(std::string path, std::vector<std::string> datavector, std::vector<std::string> signatures, std::vector<std::string> virusname)
{
    DIR *dir;
    struct dirent *entity;
    std::string newpath;
    dir=opendir(path.c_str());
    if(dir==nullptr)
    {
        std::cout<<"could not open the directory"<<std::endl;
        exit(1);
    }
    else
    {
        while((entity=readdir(dir))!=nullptr)
        {
            if(entity->d_name[0] != '.')
            {
                newpath= path + '/' +std::string(entity->d_name);               
                if(entity->d_type==DT_DIR)
                {
                    treverase(newpath, datavector, signatures, virusname);
                }
                else if(entity->d_type==DT_REG)
                {
                    compare(newpath, signatures, virusname);
                    newpath= path + '/';
                }
            }
        }
        closedir(dir);
    }
    
    

}

std::string AV::read_binary(std::string path)
{
    using bytes = std::bitset<8>;
    if(std::ifstream file {path, std::ios::binary})
    {
        std::string result;
        unsigned char b;
        
        while(file>>std::noskipws>>b)
        {
            result+=bytes(b).to_string();
        }
        
        return result;
    }
    std::cout<<"could not read the file" <<std::endl;
    exit(1);
}

void AV::createMap(std::unordered_map<std::string, char> *um)
{
    (*um)["0000"] = '0';
    (*um)["0001"] = '1';
    (*um)["0010"] = '2';
    (*um)["0011"] = '3';
    (*um)["0100"] = '4';
    (*um)["0101"] = '5';
    (*um)["0110"] = '6';
    (*um)["0111"] = '7';
    (*um)["1000"] = '8';
    (*um)["1001"] = '9';
    (*um)["1010"] = 'a';
    (*um)["1011"] = 'b';
    (*um)["1100"] = 'c';
    (*um)["1101"] = 'd';
    (*um)["1110"] = 'e';
    (*um)["1111"] = 'f';
}
 
std::string AV::to_hex(std::string binary)
{
    int l = binary.size();
    int t = binary.find_first_of('.');
    int len_left = t != -1 ? t : l;
     
    for (int i = 1; i <= (4 - len_left % 4) % 4; i++)
    {
        binary = '0' + binary;
    }
     
    if (t != -1)    
    {
        
        int len_right = l - len_left - 1;
        
        for (int i = 1; i <= (4 - len_right % 4) % 4; i++)
        {
            binary = binary + '0';
        }   
    }
     
    std::unordered_map<std::string, char> bin_hex_map;
    createMap(&bin_hex_map);
     
    unsigned int i = 0;
    std::string hex = "";
     
    while (true)
    {
        
        hex += bin_hex_map[binary.substr(i, 4)];
        i += 4;
        if (i == binary.size())
        {
            break;
        }    
             
       
        if (binary.at(i) == '.')    
        {
            hex += '.';
            i++;
        }
    }
     
   
    return hex; 

}

std::vector<std::string> AV::read_signatures(std::vector<std::string> datavector)
{
    std::vector<std::string> signatures;
    for(unsigned int i=0; i<datavector.size(); i++)
    {
        std::string virus = datavector[i];    
        for(unsigned int j =0; j< virus.length(); j++)
        {
            if(virus[j]=='=')
            {
                j++;
                std::string hexa = virus.substr(j);
                j=virus.length();
                signatures.push_back(hexa);
            }
        }
    }
    return signatures;
}

std::vector<std::string> AV::read_virusname(std::vector<std::string> datavector)
{
    std::string tempo;
    std::vector<std::string> names;
    for(unsigned int i=0; i< datavector.size();i++)
    {
        tempo="";
        std::string temp = datavector[i];
        for(unsigned int j=0; j<temp.length();j++)
        {    
            if(temp[j]=='=')
            {
                names.push_back(tempo);
                j=temp.length();
            }
            tempo+=temp[j];
        }
    }

    return names;
}

void AV::write(std::string path, std::string name)
{
    std::ofstream write;
    write.open("dv1620.log", std::fstream::app);
    write<<"There is a virus in the file that has the following filepath " + path + " it is probebly the virus " + name + "." <<std::endl << '\n' << '\n';
    write.close();
}

void AV::compare(std::string path, std::vector<std::string> signatures, std::vector<std::string> virusname)
{
    std::string temp;
    std::string binary = read_binary(path);
    std::string hex = to_hex(binary);
    bool virus = false;
    
    for(unsigned int k =0; k<signatures.size();k++)
    {
        temp="";
        temp = signatures[k];
        
        for(unsigned int r=0;r< temp.length();r++)
        {
            if(temp[r]==hex[r])
            {
                virus = true;
            }
            else
            {
                r = temp.length();
                virus = false;
            }
        }
        if(virus == true)
        {
            
            std::string name= virusname[k];
            write(path, name);
            k = signatures.size();
        }
    }
}







