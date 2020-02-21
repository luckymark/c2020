#ifndef P12_WAREHOUSE_GOODS_H
#define P12_WAREHOUSE_GOODS_H

typedef struct {
    int g1;
    int g2;
    int g3;
    int g4;
} Goods;

Goods* init();
void show_list(Goods *goods);
void warehouse(Goods *goods);
void outbound(Goods *goods);
size_t save(Goods *goods);

#endif //P12_WAREHOUSE_GOODS_H
