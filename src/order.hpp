#ifndef ORDER_HPP
#define ORDER_HPP

typedef enum OrderType {
    LIMIT,
    MARKET
} OrderType;

typedef enum Side {
    BUY,
    SELL
} Side;

typedef struct Order {
    int id;
    int asset;
    int price;
    int quantity;
    OrderType type;
    Side side;
} Order;

#endif