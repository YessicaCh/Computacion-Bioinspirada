function fractal(fase)
%clear;clc;fase = fas;
aux = 3^fase;
for i=1: aux %y cuadrados
    for j=1:1 %x cuadrados
        x = (j-1)/aux;
        y = (i-1)/aux;
        cuad = [x,y;x+1/aux,y;x+1/aux,y+1/aux;x,y+1/aux;x,y];
        %cuad
        pintar = 1;
        ki = 0;
        kj = 0;
        for k=1:fase
            ki = mod(ceil((mod(i-1,(3^(fase-k+1)))+1)/((3^k))),2);
            kj = mod(ceil((mod(j-1,(3^(fase-k+1)))+1)/((3^k))),2);
            %ki
            %kj
            if (kj == 0 & ki==0)
                pintar = 0;
            end
        end
        vec = [i , j , x , y, ki, kj];
        %vec
        if(pintar)
            fill(cuad(:,1),cuad(:,2),'g')
        end
        hold on
    end
end
