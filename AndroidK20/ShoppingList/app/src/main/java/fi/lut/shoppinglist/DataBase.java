package fi.lut.shoppinglist;

import java.util.ArrayList;
import java.util.List;

public class DataBase {

    private ArrayList<String> testList = new ArrayList<String>();
    private ArrayList<ListItem> listItems = new ArrayList<ListItem>();

    public DataBase() {
        testList.add("init1");
    }

    public ArrayList<ListItem> getData() {
        return listItems;
    }

    public void addNewItem(String item) {
        testList.add(item);
    }

    public void addNewListItem(ListItem newItem) {
        listItems.add(newItem);
    }

    public ListItem getItem(int position) {
        return listItems.get(position);
    }

    public void removeItem(int index) {
        listItems.remove(index);
    }
}
