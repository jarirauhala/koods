# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: https://docs.scrapy.org/en/latest/topics/item-pipeline.html

from scrapy.exceptions import DropItem

class MycrawlerPipeline(object):
    def process_item(self, item, spider):
        text = item['text']
        header = item['header']
        language = item['language']
        if language == "fi" \
                and "korona" not in text\
                and "Korona" not in text\
                and "KORONA" not in text: # and "corona" not in text:# or "korona" in header:
            return item
        else:
            raise DropItem("korona mentioned at " + item['url'])