package fi.lut.shoppinglist;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;

public class ItemAdapter extends BaseAdapter {

    LayoutInflater mInflater;
    //ArrayList<String> mTestList;
    //DataBase mDb;
    ArrayList<ListItem> mListItems;


    public ItemAdapter(Context c, DataBase db) {
        mListItems = db.getData();
        //mTestList = db.getData();
        mInflater = (LayoutInflater) c.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    }

    @Override
    public int getCount() {
        return mListItems.size();
    }

    @Override
    public Object getItem(int position) {
        return mListItems.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {

        View v  = mInflater.inflate(R.layout.layout_description, null);
        TextView nameTextView = (TextView) v.findViewById(R.id.listNameTextView);
        TextView amountTextView = (TextView) v.findViewById(R.id.listAmountTextView);

        String name = mListItems.get(position).mProductName;
        String amount = mListItems.get(position).mAmount;

        nameTextView.setText(name);
        amountTextView.setText(amount);

        return v;
    }

    public void addNewItem(String item) {
        //mTestList.add(item);
    }
}
