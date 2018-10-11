#include <iostream>
#include <list>
#include <cctype>
#include <algorithm>
#include <unistd.h>
#include "figure3d.h"
#include "geomlist.h"

using namespace figures;

enum input_type{
    cylinder,
    parallelepiped,
    cube,
    pyramid,
    show_list,
    empty_list,
    Exit,
    undefined
};
input_type parse_input(const std::string &answer);

void input_figure_prompt(Figure3D* const &fig, GeomList &list);
void input_figure_prompt(Figure3D*  &&fig, GeomList &list);

int main()
{

//    Figure3D *testfig = new Parallelepiped(CubeParams(3));
//    std::cout<<*testfig<<std::endl;
//    CubeParams myparams(4);
//    testfig->setParams(myparams);
//    std::cout<<*testfig<<std::endl;
//    testfig->setParams(new ParallelepipedParams);
//    std::cout<<*testfig<<std::endl;

//    delete testfig;

//    Cube cubfig(CubeParams(3));
//    cubfig = Cube();

//    return 0;
    std::cout<<"Hello, I'm geometry expert!"<<std::endl
             <<"Do you want add some figures in my list to discover them properties? (y/n): ";
    std::string answer;
    if(!std::getline(std::cin,answer) || answer.empty() || std::tolower(answer[0]) != 'y'){
        std::cout<<"Oh, what a pitty! Bey...\n";
        return 0;
    }
    GeomList figlist;
    std::cout<<"Great! Let's start. wheach figure you want to discover?"<<std::endl;
    while(true){
        std::cout<<"Input Cylinder/Parallelepiped/Cube/Pyramid/: ";
        if(!std::getline(std::cin >> std::ws, answer)){
            goto exit;
        }
        switch (parse_input(answer)) {
        case input_type::cylinder:
            input_figure_prompt(new Cylinder(), figlist);
            break;
        case input_type::parallelepiped:
            input_figure_prompt(new Parallelepiped(), figlist);
            break;
        case input_type::cube:
            input_figure_prompt(new Cube(), figlist);
            break;
        case input_type::pyramid:
            input_figure_prompt(new Pyramid(), figlist);
            break;
        case input_type::show_list:
            std::cout<<"Your figure list:\n"
                     <<figlist<<std::endl;
            break;
        case input_type::empty_list:
            std::cout<<"Your figure list empty now!\n";
            figlist.clear();
            break;
        case input_type::Exit:
            goto exit;
            break;
        case input_type::undefined:
            std::cout<<"In my world this figure doesn't exist:) Try another one\n";
            break;
        }
    }

exit:
    std::cout<<"\nYou were my brother Anakin! I loved you... Bey\n";
    if (figlist.empty()){
        return 0;
    }
    sleep(2);
    std::cout<<"\nJoke. Ha-Ha\n"
             <<"I decide to play with your list\n"
             <<"Input some positive number: ";
    size_t step;
    if(!(std::cin>>step) || step == 0){
        std::cout<<"You are boring! Goodbey Baka\n";
        return 0;
    }
    std::cout<<"\nIt's all..."<<std::flush;
    sleep(2);
    std::cout<<" Joking again"<<std::flush;
    sleep(1);
    std::cout<<"\nMy last wish. Input please some figure type and its proporties: ";
    if(!std::getline(std::cin>>std::ws, answer)){
        std::cout<<"You are boring! Goodbey Baka\n";
        return 0;
    }

    std::unique_ptr<Figure3D> fig;
    switch (parse_input(answer)) {
    case input_type::cylinder:
        fig.reset(new Cylinder());
        break;
    case input_type::parallelepiped:
        fig.reset(new Parallelepiped());
        break;
    case input_type::cube:
        fig.reset(new Cube());
        break;
    case input_type::pyramid:
        fig.reset(new Pyramid());
        break;
    default:
        std::cout<<"You are boring! Goodbey Baka\n";
        return 0;
    }
    std::cin>>*fig;
    ExtendedGeomList exfiglist(std::move(figlist));
    exfiglist.addAfterEachNth(*fig, step);
    std::cout<<"Your figure list:\n"
             <<exfiglist<<std::endl;
}

std::string normalize(const std::string &str){
    auto last_non_empty_pos = str.find_last_not_of(" \t");
    std::string norm_str = str.substr(0, last_non_empty_pos+1);
    std::transform(norm_str.begin(),
                   norm_str.end(),
                   norm_str.begin(),
                   [](unsigned char c){return std::tolower(c);}
    );
    return norm_str;
}


input_type parse_input(const std::string &answer){

    auto norm_answer = normalize(answer);

    if(norm_answer == "cylinder") return input_type::cylinder;
    if(norm_answer == "parallelepiped") return input_type::parallelepiped;
    if(norm_answer == "cube") return input_type::cube;
    if(norm_answer == "pyramid") return input_type::pyramid;
    if(norm_answer == "show list") return input_type::show_list;
    if(norm_answer == "empty list") return input_type::empty_list;
    if(norm_answer == "exit") return input_type::Exit;
    return input_type::undefined;
}

void input_figure_prompt(Figure3D* &&fig, GeomList &list){
    while(true){
        try{
            std::cin>>*fig;
        }catch(const std::runtime_error &e){
            std::cout<<e.what()
                     <<"\nWHAT ARE YOU DOING??? We forget about it, ok? Try one more"<<std::endl;
            continue;
        }
        break;
    }
    list.push(std::move(fig));
    std::cout<<"\nFigure added\n"
             <<"--To show figures in list use \"show list\"\n"
             <<"--To empty list of figures use \"empty list\"\n"
             <<"--To exit enter \"exit\"\n"
             <<std::endl;
}

void input_figure_prompt(Figure3D* const &fig, GeomList &list){
    input_figure_prompt(fig->copy(), list);
}
