#include "recipe_generator.h"

struct Recipe *create_custom_recipe(void)
{
    struct Ingredients  *ingredients = NULL;
    struct TasteProfile *profile = NULL;
    struct Recipe       *recipe = NULL;

    // 1. Fetch the current fridge ingredients
    ingredients = get_current_ingredients();
    if (!ingredients)
        return (NULL);

    // 2. Fetch the user's taste profile
    profile = get_user_taste_profile();
    if (!profile)
        return (free_ingredients(ingredients), NULL);

    // 3. Iteratively generate a recipe candidate
    while (1)
    {
        // produce new recipe
        recipe = create_recipe(ingredients, profile);
        if (!recipe)
            return (free_ingredients(ingredients), free_taste_profile(profile), NULL);
        // ask for approval and exit the cycle if it's approved (1)
        if (get_user_approval(recipe) == APPROVED)
            break;
        // reset the recipe variable and free its memory
        free_recipe(recipe);
        recipe = NULL;
    }

    // se la memoria puntata in ingredients e profile non viene usata da recipe, pulisco
    free_ingredients(ingredients);
    free_taste_profile(profile);

    return (recipe);
}