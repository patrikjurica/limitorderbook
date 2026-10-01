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
    unsigned long id;
    unsigned int timestamp;
    unsigned int asset;
    unsigned int price;
    unsigned int quantity;
    OrderType type;
    Side side;

    Order(unsigned long id,
    unsigned int timestamp,
    unsigned int asset,
    unsigned int price,
    unsigned int quantity,
    OrderType type,
    Side side) :
    id(id),
    timestamp(timestamp),
    asset(asset),
    price(price),
    quantity(quantity),
    type(type),
    side(side)
    {}
} Order;

#endif