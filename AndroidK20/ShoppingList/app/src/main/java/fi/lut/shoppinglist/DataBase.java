package fi.lut.shoppinglist;

import java.util.ArrayList;
import java.util.List;

public class DataBase {

    private ArrayList<String> testList = new ArrayList<String>();
    private ArrayList<ListItem> listItems = new ArrayList<ListItem>();

    public DataBase() {
        testList.add("init1");
    }

    //public ArrayList<String> getData() {
    public ArrayList<ListItem> getData() {
        return listItems;
        //return testList;
    }

    public void addNewItem(String item) {
        testList.add(item);
    }

    public void addNewListItem(ListItem newItem) {
        //TODO: check if item exists
        listItems.add(newItem);
    }

    public ListItem getItem(int position) {
        return listItems.get(position);
    }
}
