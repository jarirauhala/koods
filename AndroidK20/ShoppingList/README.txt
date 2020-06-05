This is an Android application by Jari Rauhala
it was made for LUT University's course:
    CT70A9120_15.04.2020 
    Software Development Skills: Mobile 
    Anytime-course

It is an app for creating a shopping list.
The user can create items of products s/he is willing to purchase.
For every item, the user can insert details of amount, name, 
brand or price and upload an imega from gallery.
By those details a ListItem class instance is created
and saved to class DataBase.
Adding new items happens in AddItemActiity activity.
The main activity shows a ListView of all products added.
ListView is described by layout_description.xml and the data
it shows is populated by class ItemAdapter.
The amount and the name are displayed of the product.
By clicking a list item ProductDetails activity is opened
and all the details of the clicked ListItem are displayed.
The user can remove the item by clicking "Remove from shopping list"
button. It is then removed from the DataBase.

Run the app:
The app can be run on an Android device by downloading
"\koods\AndroidK20\ShoppingList\app\build\outputs\apk\debug\app-debug.apk"
to an Android device and instlling it from an resource manager app.
or by downloading "\koods\AndroidK20\ShoppingList\" and running it on an emulator
on Android Studio.

