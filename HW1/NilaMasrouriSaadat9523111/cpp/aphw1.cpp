#include "aphw1.h"

std::vector <std::vector <double >> getData(const char*path)
{
    std::string ss{};
    std::vector <std::vector <double >> row(234,std::vector <double>(8,0));
    std::ifstream iff(path);// for reading the file
    for (size_t i = 0; i < 234; i++) 
    {
        row[i][0]=1;// har radif avalin sotoon barabre 1 bzar
        std::string line{};
        std::getline(iff, line);
        std::stringstream iff(line);
        for (size_t j= 1; j <= 7; j++)
        {
           std::getline(iff,ss,',');//reading each file and saving it into a string 
           
                if(!ss.empty())
                 row[i][j]=std::stod(ss);//casting the string into double
            
        }
       row[i][3]/=100;
       row[i][4]/=100;
    }

    return row;
}

 void displayDataset(std::vector <std::vector <double >>row)
 {
     std::cout<<"bias"<<std::setw(20)<<"class"<<std::setw(20)<<"ta"<<std::setw(20)<<"coding"<<std::setw(20)<<"studying"<<std::setw(20)<<"background"<<std::setw(20)<<"mind"<<std::setw(20)<<"grade"<<std::endl;
      for (size_t i = 0; i < 234; i++)
    {
        std::cout<<std::endl;

        for (size_t j= 0; j < 7; j++)
        {
            std::cout<<row[i][j]<<std::setw(20);
        }
        std::cout<<row[i][7];
    }
    std::cout<<std::endl;
 }
  double grade(std::vector <double > w, std::vector <double > x)
  { 
      double fgrade{};
    for (size_t i = 0; i < 7; i++)
    {
         fgrade+=w[i]*x[i];
    }
    
    return fgrade;
  }
   double J(std::vector<double>w, std::vector<std::vector<double>>data)
  {
      double answer{}, estimated{},real{};
    for (size_t i = 0; i < 234; i++)
    {
        estimated=grade(w,data[i]);
        real=data[i][7];
        answer+=pow((estimated-real),2);
    }
    answer=answer/468;
    return answer;
  }

std::vector<double> train(std::vector<std::vector<double>> data, std::vector<double> w, double alpha, size_t max_iters, double min_cost, size_t verbose)
{
    size_t cnt{};
   std::vector<double> sum(8,0);
   while(cnt<max_iters)//for iteration
   {
    if(verbose)
         std::cout<<"last value of cost function"<<J(w,data)<<std::endl;
    
        if(J(w,data)>min_cost)
        {
            for (size_t j = 0; j < 234; j++)
            {
                for (size_t i = 0; i< 7; i++)
                {
                    sum[i]+=(grade(w,data[j])-data[j][7])*data[j][i];    
                }

            }
            for (size_t i = 0; i< 7; i++)
            {
            w[i]= w[i] - alpha*(sum[i]/234);
            sum[i]=0;
            }
            
        }
        else
            break;
    if(verbose)
        std::cout<<"current value of cost function"<<J(w,data)<<std::endl;
    
    cnt++;
   }
    return w;
}
void displayOutput(std::vector<std::vector<double>>data, std::vector<double>w)//weight vector obtained from the **train** function
{
    std::cout<<"NO"<<std::setw(20)<<"Real Grade"<<std::setw(20)<<"Estimated Grade"<<std::endl;
    for (size_t i = 0; i < 234; i++)
    {
        std::cout<<i+1<<std::setw(20)<<data[i][7]<<std::setw(20)<<grade(w,data[i])<<std::endl;
    }
    
}
void save(std::vector<double> w, const char* name)
{
     std::ofstream out(name);
     for (size_t i = 0; i < 7; i++)
     {
         out<<w[i]<<",";
     }
     
}
std::vector<double> load(const char*name)
{
       std::ifstream inn(name);
       std::vector<double>w(8,0);
       std::string ss{};
      for (size_t i = 0; i < 8; i++)
     {
         std::getline(inn,ss,',');//reading each file and saving it into a string 
           
                if(!ss.empty())
                 w[i]=std::stod(ss);//casting the string into double
            
     }
     
return w;
}
double predict(std::vector<double>newstu, std::vector<double>w)
{
    return grade(w,newstu);
}