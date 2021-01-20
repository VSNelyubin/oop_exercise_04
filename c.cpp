// Written by VSNelyubin, m80-206b-19, Original Code, do not steal!

#include <iostream>

#include <cmath>

#include <iomanip>

#include <stdio.h>

#include <stdlib.h>

#include <vector>

double dabs(double a){
	if(a<0){return -a;}
	return a;
}

template <class T>
double dist(std::pair<T,T> a,std::pair<T,T> b){
	double rez=std::pow((double)a.first-(double)b.first,2);
	rez+=std::pow((double)a.second-(double)b.second,2);
	return std::sqrt(rez);
}

template <class T>
class Figure{
	public:	std::pair<T,T>*cord;
	int verNum;
	Figure(int vern){
		verNum=vern;
		cord=new std::pair<T,T>[vern];
	}
	~Figure(){
		delete[] cord;
	}
};

template <class T>
bool checkEven(Figure<T>*ta){
    if(ta->verNum<3){return true;}
    double rez=dist(ta->cord[0],ta->cord[ta->verNum-1]);
    for(int arei=1;arei<ta->verNum;arei++){
        if(rez!=dist(ta->cord[arei],ta->cord[arei-1])){return false;}
    }
	rez=dist(ta->cord[0],ta->cord[ta->verNum-2]);
	if(rez!=dist(ta->cord[1],ta->cord[ta->verNum-1])){return false;}
    for(int arei=2;arei<ta->verNum;arei++){
        if(rez!=dist(ta->cord[arei],ta->cord[arei-2])){return false;}
    }

    return true;
}


template <class T>
double figArea(Figure<T>*ta){
	if(ta->verNum<3){return 0;}
	double rez,res=0;
	for(int arei=2;arei<ta->verNum;arei++){
		rez=ta->cord[0].first*(ta->cord[arei-1].second-ta->cord[arei].second);
		rez+=ta->cord[arei-1].first*(ta->cord[arei].second-ta->cord[0].second);
		rez+=ta->cord[arei].first*(ta->cord[0].second-ta->cord[arei-1].second);
		res+=dabs(rez/2);
	}
	return res;
}

template <class T>
std::pair<double,double> finCenter(Figure<T>*t){
	std::pair<double,double>rez;
	rez.first=0;rez.second=0;
	for(int arei=0;arei<t->verNum;arei++){
		rez.first+=(double)t->cord[arei].first;
		rez.second+=(double)t->cord[arei].second;
	}
	rez.first=rez.first/(double)t->verNum;
	rez.second=rez.second/(double)t->verNum;
	return rez;
}

template <class T>
std::ostream& operator << (std::ostream & out, Figure<T> &c) {
        for(int arei=0;arei<c.verNum;arei++){
                out<<c.cord[arei].first<<" : "<<c.cord[arei].second<<"\n";
        }
        return out;
}

template <class T>
std::istream& operator >> (std::istream & out, Figure<T> &c) {
        for(int arei=0;arei<c.verNum;arei++){
                out>>c.cord[arei].first>>c.cord[arei].second;
        }
		if(!checkEven(&c)){std::cout<<"figure sides are not even\n";}
        return out;
}



template <class T>
class pent : public Figure<T> { //XD public figure
        public:
        	pent():Figure<T>(5){
        }
};
template <class T>
class hex : public Figure<T> { //XD public figure
        public:
        	hex():Figure<T>(6){
        }
};
template <class T>
class oct : public Figure<T> { //XD public figure
        public:
        	oct():Figure<T>(8){
        }
};


int main(){
	std::vector<std::tuple<Figure<double>*>> arr;
	//std::tuple<Figure<double>*> ar;
	pent<double>*a;
	hex<double>*b;
	oct<double>*c;
	char fgt;
	int len;
	std::cin>>len;
	for(int i=0;i<len;i++){
		std::cin>>fgt;
		if(fgt=='p'){
			a=new pent<double>;
			std::cin>>*a;
			//arr.push_back(a);
			arr.push_back(std::make_tuple(a));
		}
		else if(fgt=='h'){
			b=new hex<double>;
			std::cin>>*b;
			//arr.push_back(b);
			arr.push_back(std::make_tuple(b));
			//std::tuple_cat(ar,std::make_tuple(b));
		}
                else if(fgt=='o'){
                        c=new oct<double>;
                        std::cin>>*c;
                        //arr.push_back(c);
						arr.push_back(std::make_tuple(c));
			//std::tuple_cat(ar,std::make_tuple(c));
		}
		else{
			i--;
			std::cout<<"please specify what figure you are inputting: p for pentagon, h for hexagon, o for octagon.\n";
		}
	}
	for(int i=0;i<len;i++){
		std::cout<<*(std::get<0>(arr[i]))<<"\n";
	}
//printf("bruh1\n");
	int dl,dt;
	std::cout<<"\n";
	std::cin>>dl;
	for(int i=0;i<dl;i++){
		std::cin>>dt;
		if(dt<len){
			arr.erase(arr.begin()+dt);
			len--;
		}
	}
	for(int i=0;i<len;i++){
    	std::cout<<*(std::get<0>(arr[i]))<<"\n\n";
    }
//printf("bruh2\n");
	double surf=0;
	for(int i=0;i<len;i++){
		surf+=figArea(std::get<0>(arr[i]));
		std::cout<<finCenter((std::get<0>(arr[i]))).first<<" : "<<finCenter((std::get<0>(arr[i]))).second<<"\n\n";
	}
	std::cout<<"Sum of all surfaces is "<<surf<<"\n";
	/*rectangle testo;
//	cout<<"input rectangle\n";
	cin>>testo;
//	cout<<"input yes\n";
	cout<<testo<<"\n";*/
	return 0;
}
