#include <iostream>
#include <vector>
class Angajat{
  protected:
  std::string nume;
  float salariu_baza;
  float salariu_net;
  float salariu_brut;
  std::string functie;
  float procent_taxe_salariu;
  public:
  Angajat(std::string nume, float salariu_baza):nume(nume), salariu_baza(salariu_baza) {}
  virtual float get_salariu_net(){
      return 0;
  }
  
  virtual float get_salariu_brut()
  {
      return salariu_baza;
  }
  std::string get_nume()
  {
      return nume;
  }
  void marire_salariu(float a)
  {
      std::cout<<nume<<std::endl;
      std::cout<<"Salariu de baza vechi: "<<salariu_baza<<std::endl;
      std::cout<<"Salariu de baza nou: "<<(salariu_baza*(100+a))/100<<std::endl;
  }
  void afisare()
  {
      std::cout<<nume<<std::endl;
      std::cout<<functie<<std::endl;
  }
  void afisare_salarii()
  {
      std::cout<<nume<<std::endl;
      std::cout<<"Salariu brut: "<<salariu_brut<<std::endl;
      std::cout<<"Salariu Net: "<<salariu_net<<std::endl;
  }
  std::string get_functie()
  {
      return functie;
  }
  virtual ~Angajat()
  {
      std::cout<<"Destructor Angajat"<<std::endl;
  }
};
class Analist: public Angajat{
    public:
    Analist(std::string nume, float sal_b):Angajat(nume,sal_b)
    {
        functie="Analist";
        procent_taxe_salariu=40;
        salariu_brut=get_salariu_brut();
        salariu_net=get_salariu_net();
    }
    float get_salariu_net()
    {
        return (salariu_baza*(float)(100-procent_taxe_salariu))/100;
    }
    ~Analist()
    {
        std::cout<<"Destructor Analist"<<std::endl;
    }
};
class Programator: public Analist{
    protected:
    float procent_deducere_salariu_it;
    public:
    Programator(std::string nume, float sal_b):Analist(nume, sal_b)
    {
        functie="Programator";
        procent_deducere_salariu_it=10;
        salariu_brut=get_salariu_brut();
        salariu_net=get_salariu_net();
    }
    float get_salariu_net()
    {
        return (salariu_baza*(float)((100-procent_taxe_salariu)+procent_deducere_salariu_it))/100;
    }
    ~Programator()
    {
        std::cout<<"Destructor Programator"<<std::endl;
    }
};
class LiderEchipaProgramare: public Programator{
   protected:
   float bonus_vechime_functie;
   int vechime_functie;
   public:
   float get_salariu_brut()
   {
       return salariu_baza+(bonus_vechime_functie*vechime_functie);
   }
   float get_salariu_net()
   {
       return ((salariu_baza+(bonus_vechime_functie*vechime_functie))*((100-procent_taxe_salariu)+procent_deducere_salariu_it))/100;
   }
   LiderEchipaProgramare(std::string nume, float sal_b, int vechime_functie):Programator(nume, sal_b), vechime_functie(vechime_functie){
       functie="LiderEchipaProgramare";
       bonus_vechime_functie=500;
       salariu_brut=get_salariu_brut();
       salariu_net=get_salariu_net();
   }
   
};
class FirmaProgramare{
    private:
    Angajat **v;
    public:
    void afiseaza_angajat()
    {
        
    }
    void mareste_salarii(float a, float b, float c)
    {
        
    }
    void promoveaza(std::string a)
    {
        
    }
};
int main()
{
    int nr_angajati, an_vec, contor, procent_marire_a, procent_marire_p, procent_marire_l;
    std::string nume, rol, rol_a;
    float sal_b, p_t_s;
    std::vector<Angajat*>vec;
    std::cin>>nr_angajati;
    std::cin.ignore();
    for(int i=0;i<nr_angajati;i++)
    {
        
        getline(std::cin, nume);
        std::cin>>rol;
        if(rol=="Programator")
        {
            std::cin>>sal_b;
            vec.push_back(new Programator(nume, sal_b));
        }
        if(rol=="Analist")
        {
            std::cin>>sal_b;
            vec.push_back(new Analist(nume, sal_b));
        }
        if(rol=="LiderEchipaProgramare")
        {
            std::cin>>sal_b;
            std::cin>>an_vec;
            vec.push_back(new LiderEchipaProgramare(nume, sal_b, an_vec));
        }
        std::cin.ignore();
    }
    std::cin>>contor;
    switch(contor)
    {
        case 1:
        {
            for(int i=0;i<nr_angajati;i++)
            vec[i]->afisare();
        }
        break;
        case 2:
        {
            for(int i=0;i<nr_angajati;i++)
            {
            vec[i]->afisare_salarii();
            }
        }
        break;
        case 3:
        {
           for(int i=0;i<3;i++)
           {
               std::cin>>rol_a;
               if(rol_a=="Analist")
               std::cin>>procent_marire_a;
               if(rol_a=="Programator")
               std::cin>>procent_marire_p;
               if(rol_a=="LiderEchipaProgramare")
               std::cin>>procent_marire_l;
           }
           for(int i=0;i<nr_angajati;i++)
           {
               if(vec[i]->get_functie()=="Analist")
               vec[i]->marire_salariu(procent_marire_a);
               if(vec[i]->get_functie()=="Programator")
               vec[i]->marire_salariu(procent_marire_p);
               if(vec[i]->get_functie()=="LiderEchipaProgramare")
               vec[i]->marire_salariu(procent_marire_l);
           }
        }
        break;
        case 4:
        {
            std::cin.ignore();
            getline(std::cin, nume);
            std::cin>>rol;
            for(int i=0;i<nr_angajati;i++)
            {
                if(vec[i]->get_nume()==nume)
                {
                    delete vec[i];
                    if(rol=="LiderEchipaProgramare")
                    vec.push_back(new LiderEchipaProgramare(nume, 4000/*placeholder*/, 0));
                    if(rol=="Programator")
                    vec.push_back(new Programator(nume, 4000));
                }
            }
            for(int i=0;i<nr_angajati;i++)
            vec[i]->afisare();
        }
        break;
    }
    
    
    return 0;
}

