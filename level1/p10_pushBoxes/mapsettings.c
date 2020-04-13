#include "aboutmap.h"

pos Switch(int**map,char c,pos loc){
    switch (c) {
        case 'W' :
            if (loc.x < 1 || 2 == *((int *) map + col * (loc.x - 1) + loc.y))
            {
                return loc;
            }
            else{
                if(*((int *) map + col * (loc.x-1) + loc.y)!=4&&*((int *) map + col * (loc.x-1) + loc.y)!=5){
                    *((int *) map + col * (loc.x-1) + loc.y) = *((int *) map + col * (loc.x-1) + loc.y) + 2;
                    *((int *) map + col * loc.x + loc.y) = *((int *) map + col * loc.x + loc.y) - 2;
                    loc.x-= 1;
                    loc.cnt+= 1;
                    return loc;
                } else{
                    if(4==*((int *) map + col * (loc.x-1) + loc.y )){
                        if(0==loc.bag){
                            *((int *) map + col * (loc.x-1) + loc.y) = *((int *) map + col * (loc.x-1) + loc.y) - 1;
                            *((int *) map + col * loc.x + loc.y)=*((int *) map + col * loc.x + loc.y)-2;
                            loc.bag=1;loc.x-=1;loc.cnt+=1;
                            return loc;
                        }else return loc;
                    }
                    if(5==*((int *) map + col * (loc.x-1) + loc.y)){
                        if(1==loc.bag) {
                            *((int *) map + col * (loc.x-1) + loc.y ) = *((int *) map + col * (loc.x-1) + loc.y) - 2;
                            *((int *) map + col * loc.x + loc.y)=*((int *) map + col * loc.x + loc.y)-2;
                            loc.x-=1;loc.bag=0;loc.cnt+=1;
                            return loc;
                        }else {
                            return loc;
                        }
                    }
                }
            }
        case 'A' :
            if (loc.y < 1 || 2 == *((int *) map + col * loc.x + loc.y-1))
            {
                return loc;
            }
            else{
                if(*((int *) map + col * loc.x + loc.y - 1)!=4&&*((int *) map + col * loc.x + loc.y - 1)!=5){
                    *((int *) map + col * loc.x + loc.y - 1) = *((int *) map + col * loc.x + loc.y - 1) + 2;
                    *((int *) map + col * loc.x + loc.y) = *((int *) map + col * loc.x + loc.y) - 2;
                    loc.y -= 1;
                    loc.cnt += 1;
                    return loc;
                }
                else{
                if(4==*((int *) map + col * loc.x + loc.y - 1)){
                    if(0==loc.bag){
                        *((int *) map + col * loc.x + loc.y - 1) = *((int *) map + col * loc.x + loc.y - 1) - 1;
                        *((int *) map + col * loc.x + loc.y)=*((int *) map + col * loc.x + loc.y)-2;
                        loc.bag=1;loc.y-=1;loc.cnt+=1;
                        return loc;
                    }else return loc;
                }
                if(5==*((int *) map + col * loc.x + loc.y - 1)){
                    if(1==loc.bag) {
                        *((int *) map + col * loc.x + loc.y - 1) = *((int *) map + col * loc.x + loc.y - 1) - 2;
                        *((int *) map + col * loc.x + loc.y)=*((int *) map + col * loc.x + loc.y)-2;
                        loc.y-=1;loc.bag=0;loc.cnt+=1;
                        return loc;
                    }else {
                        return loc;
                    }
                }
            }
            }
        case 'S' :
            if (loc.y > 4 || 2 == *((int *) map + col * (loc.x + 1) + loc.y))
            {
                return loc;
            }
            else{
                if(*((int *) map + col * (loc.x+1) + loc.y)!=4&&*((int *) map + col * (loc.x+1) + loc.y)!=5){
                    *((int *) map + col * (loc.x+1) + loc.y) = *((int *) map + col * (loc.x+1) + loc.y) + 2;
                    *((int *) map + col * loc.x + loc.y) = *((int *) map + col * loc.x + loc.y) - 2;
                    loc.x+= 1;
                    loc.cnt+= 1;
                    return loc;
                } else{
                    if(4==*((int *) map + col * (loc.x+1) + loc.y )){
                        if(0==loc.bag){
                            *((int *) map + col * (loc.x+1) + loc.y) = *((int *) map + col * (loc.x+1) + loc.y) - 1;
                            *((int *) map + col * loc.x + loc.y)=*((int *) map + col * loc.x + loc.y)-2;
                            loc.bag=1;loc.x+=1;loc.cnt+=1;
                            return loc;
                        }else return loc;
                    }
                    if(5==*((int *) map + col * (loc.x+1) + loc.y)){
                        if(1==loc.bag) {
                            *((int *) map + col * (loc.x+1) + loc.y ) = *((int *) map + col * (loc.x+1) + loc.y) - 2;
                            *((int *) map + col * loc.x + loc.y)=*((int *) map + col * loc.x + loc.y)-2;
                            loc.x+=1;loc.bag=0;loc.cnt+=1;
                            return loc;
                        }else {
                            return loc;
                        }
                    }
                }
            }
        case 'D':
            if (loc.x > 4 || 2 == *((int *) map + col * loc.x + loc.y+1))
            {
                return loc;
            }
            else{
                if(*((int *) map + col * loc.x + loc.y + 1)!=4&&*((int *) map + col * loc.x + loc.y + 1)!=5){
                    *((int *) map + col * loc.x + loc.y + 1) = *((int *) map + col * loc.x + loc.y + 1) + 2;
                    *((int *) map + col * loc.x + loc.y) = *((int *) map + col * loc.x + loc.y) - 2;
                    loc.y += 1;
                    loc.cnt += 1;
                    return loc;
                } else{
                    if(4==*((int *) map + col * loc.x + loc.y + 1)){
                        if(0==loc.bag){
                        *((int *) map + col * loc.x + loc.y + 1) = *((int *) map + col * loc.x + loc.y + 1) - 1;
                        *((int *) map + col * loc.x + loc.y)=*((int *) map + col * loc.x + loc.y)-2;
                        loc.bag=1;loc.y+=1;loc.cnt+=1;
                        return loc;
                        }else return loc;
                    }
                    if(5==*((int *) map + col * loc.x + loc.y + 1)){
                        if(1==loc.bag) {
                            *((int *) map + col * loc.x + loc.y + 1) = *((int *) map + col * loc.x + loc.y + 1) - 2;
                            *((int *) map + col * loc.x + loc.y)=*((int *) map + col * loc.x + loc.y)-2;
                            loc.y+=1;loc.bag=0;loc.cnt+=1;
                            return loc;
                        }else {
                            return loc;
                        }
                    }
                }
            }
        default: return loc;
    }
//    printf("%c",*((char*)go + col*loc.x + loc.y));
}