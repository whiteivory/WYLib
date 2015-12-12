<?php
namespace WYLib;
use WYLib\Page;
class PageGen
{
    private $rownum;
    private $rowper;
    private $pagenum;//当前页
    private $barnum;
    
    private $limit;
    private $offset;
    private $bar;
    private $url;

    public function __construct($rownum,$rowper,$pagenum,$url,$barnum=5){
        $this->rownum=$rownum;
        $this->rowper=$rowper;
        $this->pagenum=$pagenum;
        $this->barnum=$barnum;
        $this->setUrl($url);
        $this->initBarnum();
    }
    //url处理
    public function setUrl($url){
        $url=preg_replace('/[&\?]page=\d+/', '', $url);//去掉url的?page=2 或者&page=11
        $prefix='?';
        if(strpos($url, '?') !=0){
            $prefix='&';
        }
        $this->url=$url.$prefix.'page=';
    }
    public function initBarnum(){
        $this->barnum=($this->barnum>(floor($this->rownum/$this->rowper)+1)?floor($this->rownum/$this->rowper)+1:$this->barnum);
    }
    public function genPdo(){
        if($this->bar==null)
            $this->init();
        return array(
            "limit"=>$this->limit,
            "offset"=>$this->offset
        );
    }
    public function init(){
        $pagenums=floor($this->rownum/$this->rowper);//155/10=15页
        $this->offset=($this->pagenum==$pagenums?$this->rownum%$this->rowper:$this->rowper);
        $this->limit=($this->pagenum-1)*$this->rowper;

        $this->bar=array();
        //添加pre
        $pre=new Page(Page::PRE, Page::NOSELECTED, 0, Page::EDITABLE,$this->url.($this->pagenum-1));
        if($this->pagenum==1) $pre->setEditable(Page::NOT_EDITABLE);
        $this->bar[]=$pre;
        //添加第一页
        $page1=new Page(Page::NOR,Page::NOSELECTED,1,Page::EDITABLE,$this->url."1");
        if($this->pagenum==1){
            $page1->setEditable(Page::NOT_EDITABLE);
            $page1->setSelected(page::SELECTED);
        }
        $this->bar[]=$page1;
        $start=2;
        $end=$pagenums-1;
        //添加...
        $flag=0;
        if($pagenums>$this->barnum){
            //添加前...
            if(floor(($this->barnum-1)/2)+1<$this->pagenum){
                $pagelue1=new Page(Page::LUE,Page::NOSELECTED,0,page::NOT_EDITABLE,0);
                $start=$this->pagenum+1-floor(($this->barnum-1)/2);
                $this->bar[]=$pagelue1;
            }
            //编辑后...但不添加
            if($this->pagenum<$pagenums-(floor($this->pagenum/2))){
                $flag=1;
                $end=$this->pagenum+floor($this->barnum/2);
            }
        }
        //添加数字
        for($i=$start;$i<=$end;$i++){
            $page=new Page(Page::NOR, Page::NOSELECTED, $i, Page::EDITABLE, $this->url."$i");
            if($i==$this->pagenum){
                $page->setSelected(Page::SELECTED);
                $page->setEditable(Page::NOT_EDITABLE);
            }
            $this->bar[]=$page;
        }
        //添加后...
        if($flag==1){
            $pagelue2=new Page(Page::LUE,Page::NOSELECTED,0,page::NOT_EDITABLE,0);
            $this->bar[]=$pagelue2;
        }
        //添加最后一页
        $pageend=new Page(Page::NOR,Page::NOSELECTED,$pagenums,Page::EDITABLE,$this->url."$pagenums");
        if($this->pagenum==$pagenums){
            $pageend->setEditable(Page::NOT_EDITABLE);
            $pageend->setSelected(page::SELECTED);
        }
        $this->bar[]=$pageend;
        //添加latter
        $latter=new Page(Page::LAT, Page::NOSELECTED, 0, Page::EDITABLE,$this->url.($this->pagenum+1));
        if($this->pagenum==$pagenums) $latter->setEditable(Page::NOT_EDITABLE);
        $this->bar[]=$latter;
        
    }
    public function genBar(){
        if($this->bar==null)
            $this->init();
        return $this->bar;
    }
}
?>