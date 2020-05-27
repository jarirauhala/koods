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
            }
        });

        itemsListView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Intent showProductDetailsActivity =
                        new Intent (getApplicationContext(), ProductDetails.class);
                String productAmount = db.getItem(position).mAmount + "";
                String productName = db.getItem(position).mProductName;
                String productBrand = db.getItem(position).mBrand;
                String productPrice = db.getItem(position).mPrice + "";
                Bitmap productPicture = db.getItem(position).mPic;

                showProductDetailsActivity.putExtra("fi.lut.PRODUCT_AMOUNT", productAmount);
                showProductDetailsActivity.putExtra("fi.lut.PRODUCT_NAME", productName);
                showProductDetailsActivity.putExtra("fi.lut.PRODUCT_BRAND", productBrand);
                showProductDetailsActivity.putExtra("fi.lut.PRODUCT_PRICE", productPrice);
                showProductDetailsActivity.putExtra("fi.lut.DB_POSITION", position);

                ByteArrayOutputStream btArrayOutputStream = new ByteArrayOutputStream();
                productPicture.compress(Bitmap.CompressFormat.JPEG, 50, btArrayOutputStream );
                showProductDetailsActivity.putExtra("fi.lut.PRODUCT_PICTURE", btArrayOutputStream.toByteArray());

                startActivityForResult(showProductDetailsActivity, 5);
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, @Nullable Intent data) {
        super.onActivityResult(requestCode, resultCode, data);

        if (resultCode == Activity.RESULT_OK) { // from AddItemActiity
            String newAmount = data.getStringExtra("fi.lut.AMOUNT_INPUT");
            String newName = data.getStringExtra("fi.lut.NAME_INPUT");
            String newBrand = data.getStringExtra("fi.lut.BRAND_INPUT");
            String newPrice = data.getStringExtra("fi.lut.PRICE_INPUT");

            Bitmap bitmap = BitmapFactory.decodeByteArray(
                    data.getByteArrayExtra("fi.lut.PIC_INPUT"),
                    0,
                    data.getByteArrayExtra("fi.lut.PIC_INPUT").length);

            ListItem newItem = new ListItem(newAmount, newName, newBrand, newPrice, bitmap);
            db.addNewListItem(newItem);
            itemsListView.setAdapter(itemAdapter);
        }
        else if(resultCode == 3) { // from ProductDetails, to remove the item
            assert data != null;
            boolean removeItemFlag = data.getBooleanExtra("fi.lut.REMOVE_FLAG", false);
            int db_position = data.getIntExtra("fi.lut.DB_POSITION", -1);

            if (removeItemFlag) {
                db.removeItem(db_position);
                itemsListView.setAdapter(itemAdapter);
            }
        }
        else {
            // error
        }
    }
}
