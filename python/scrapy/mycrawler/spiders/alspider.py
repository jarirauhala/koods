# -*- coding: utf-8 -*-
import scrapy
from ..items import MycrawlerItem
from datetime import datetime

class AlspiderSpider(scrapy.Spider):
    name = 'alspider'
    allowed_domains = ['yle.fi']
    start_urls = ['https://yle.fi/uutiset/']

    known_urls = []

    def parse(self, response):

        now = datetime.now().time()
        this_url = response.url

        print("now crawling breadth first:" + this_url)

        paragraphs = response.xpath('//p/text()').extract()
        h1 = response.xpath('//h1/text()').extract_first()
        date = response.xpath('//*[@class="yle__article__date--published"]/text()').extract_first()
        author = response.xpath(
            '//*[@class="yle__article__author__name__text"]/text()')\
            .extract_first()
        urls = response.xpath('//a/@href').extract()
        language = response.xpath('/html/@lang').extract_first()

        print("found " + str(len(urls)) + " urls from site")

        text = ""
        for p in paragraphs:
            text += p

        items = MycrawlerItem()
        items['url'] = this_url
        items['publish_date'] = date
        items['author'] = author
        items['header'] = h1
        items['text'] = text
        items['crawl_time'] = now.strftime("%H:%M:%S")
        items['language'] = language

        yield items

        urls_to_visit = []
        fullurl = ""

        for url in urls:
            if "https://yle.fi/uutiset" in url:
                fullurl = url
                urls_to_visit.append(fullurl)

            elif "/uutiset/" in url:
                fullurl = "https://yle.fi" + url
                urls_to_visit.append(fullurl)

        for url in urls_to_visit:
            yield scrapy.Request(url)
