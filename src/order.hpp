#ifndef ORDER_HPP
#define ORDER_HPP

typedef enum OrderType {
    LIMIT,
    MARKET,
    IOC
} OrderType;

typedef enum Side {
    BUY,
    SELL
} Side;

typedef struct Order {
    unsigned int id;
    unsigned int timestamp;
    unsigned int asset;
    unsigned int price;
    unsigned int quantity;
    OrderType type;
    Side side;
} Order;

#endif