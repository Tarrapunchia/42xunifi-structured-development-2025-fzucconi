#include "food_order.h"

int process_food_order(struct OrderRequest *request)
{
    // check if request is valid
    if (!request /* || optional deep check on req, such as check_request(request)*/)
        return (REQ_ERROR);

    struct OrderConfirmation *confirmation = NULL;

    // check the state of the restaurant
    // open
    if (check_restaurant_status(request) == OPEN)
        confirmation = create_standard_confirmation();
    // closed
    else
        confirmation = create_preorder_confirmation();

    // free the request?
    free(request);

    // check if confirmation is valid
    if (!confirmation)
        return (CONF_ERROR);

    // send the actual response
    return (send_confirmation_notification(confirmation), OK);
}