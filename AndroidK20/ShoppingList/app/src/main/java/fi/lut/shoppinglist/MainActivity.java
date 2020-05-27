package fi.lut.shoppinglist;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;

import java.io.ByteArrayOutputStream;
import java.net.URI;
import java.util.ArrayList;
import java.util.List;

public class MainActivity extends AppCompatActivity {

    ListView itemsListView;
    Button addButton;
    DataBase db;

    String mNewProductName = "";

    ItemAdapter itemAdapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        itemsListView = (ListView) findViewById(R.id.itemsListView);
        addButton = (Button) findViewById(R.id.addButton);

        db = new DataBase();
        itemAdapter = new ItemAdapter(this, db);

        addButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Intent addNewItem = new Intent(getApplicationContext(), AddItemActiity.class);
                addNewItem.putExtra("fi.lut.NEW_PRODUCT_NAME", mNewProductName);
                startActivityForResult(addNewItem, 0);
                //startActivity(addNewItem);
            }
        });

        itemsListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                System.out.println("OJ83");

                Intent showProductDetailsActivity =
                        new Intent (getApplicationContext(), ProductDetails.class);
                String productName = db.getItem(position).mProductName;
                String productBrand = db.getItem(position).mBrand;
                String productPrice = db.getItem(position).mPrice + "";
                Bitmap productPicture = db.getItem(position).mPic;
                //Uri picUri = db.getItem(position).mPictureURI;
                System.out.println("OJ82");


                ByteArrayOutputStream btArrayOutputStream = new ByteArrayOutputStream();
                productPicture.compress(Bitmap.CompressFormat.JPEG, 50, btArrayOutputStream );
                showProductDetailsActivity.putExtra("fi.lut.PRODUCT_PICTURE", btArrayOutputStream.toByteArray());

                System.out.println("OJ80");


                showProductDetailsActivity.putExtra("fi.lut.PRODUCT_NAME", productName);
                showProductDetailsActivity.putExtra("fi.lut.PRODUCT_BRAND", productBrand);
                showProductDetailsActivity.putExtra("fi.lut.PRODUCT_PRICE", productPrice);
                //showProductDetailsActivity.setData(picUri);
                //showProductDetailsActivity.putExtra("fi.lut.PRODUCT_PICTURE", productPicture);
                // todo: picture
                //showProductDetailsActivity.putExtra("fi.lut.OTHER_INFO", "INforillo");

                System.out.println("OJ81");


                startActivity(showProductDetailsActivity);
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        System.out.println("oj300a");

        super.onActivityResult(requestCode, resultCode, data);

        System.out.println("oj3066");


        if (resultCode == Activity.RESULT_OK) {
            System.out.println("oj300");

            String newName = data.getStringExtra("fi.lut.NAME_INPUT");
            String newBrand = data.getStringExtra("fi.lut.BRAND_INPUT");
            String newPrice = data.getStringExtra("fi.lut.PRICE_INPUT");
            //Uri picURI = data.getData();
            Bitmap bitmap = BitmapFactory.decodeByteArray(
                    data.getByteArrayExtra("fi.lut.PIC_INPUT"),0,data.getByteArrayExtra("fi.lut.PIC_INPUT").length);

            /*
            if(data.hasExtra("fi.lut.PIC_INPUT")) {
                bitmap = BitmapFactory.decodeByteArray(
                        data.getByteArrayExtra("fi.lut.PIC_INPUT"),0,data.getByteArrayExtra("fi.lut.PIC_INPUT").length);
            }

             */

            System.out.println("oj304");



            ListItem newItem = new ListItem(newName, newBrand, newPrice, bitmap);
            db.addNewListItem(newItem);
            itemsListView.setAdapter(itemAdapter);
        }
        else {
            System.out.println("oj3004");

        }



    }
}
