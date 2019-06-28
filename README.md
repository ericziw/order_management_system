# order_management_system
simple data management system with select commands
replicating a POS system

## commands

* update: locates customer, and updates customer info.
* place: locates customer, and places customer's orders.
* fulfill: locates order, and fulfills the order, then removes the order from active orders list.

## commands' syntax

* update: update (first name) (last name) (updated first name) (updated last name) (updated age) (updated address number) (updated address name) (updated address suffix)
* place: place (first name) (last name) (price) (item amount) (items)...
* fulfill: fulfill (order number)
