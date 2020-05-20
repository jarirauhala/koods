package fi.lut.shoppinglist;

import android.content.Context;
import android.provider.ContactsContract;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;

public class ItemAdapter extends BaseAdapter {

    LayoutInflater mInflater;
    ArrayList<String> mTestList;
    //DataBase mDb;


    public ItemAdapter(Context c, DataBase db) {

        mTestList = db.getData();
        mInflater = (LayoutInflater) c.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
    }

    @Override
    public int getCount() {
        return mTestList.size();
    }

    @Override
    public Object getItem(int position) {
        return mTestList.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {

        View v  = mInflater.inflate(R.layout.layout_description, null);
        TextView testTextView = (TextView) v.findViewById(R.id.testTextView);

        String name = mTestList.get(position);

        testTextView.setText(name);

        return v;
    }

    public void addNewItem(String item) {
        mTestList.add(item);
    }
}
