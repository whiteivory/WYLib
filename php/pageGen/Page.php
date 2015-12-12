<?php
namespace WYLib;
class Page
{
    const PRE='pre';
    const LAT='latter';
    const LUE='...';
    const NOR='normal';
    private $type;//上面四种
    
    const SELECTED='selected';
    const NOSELECTED='noselected';
    private $selected;
    
    const EDITABLE='editable';
    const NOT_EDITABLE='noteditale';
    private $editable;
    
    private $num;
    private $url;

 public function __construct($type,$selected,$num,$editable,$url){
        $this->type=$type;
        $this->selected=$selected;
        $this->num=$num;
        $this->editable=$editable;
        $this->url=$url;
    }

    /**
     * @return the $url
     */
    public function getUrl()
    {
        return $this->url;
    }
    
    /**
     * @param field_type $url
     */
    public function setUrl($url)
    {
        $this->url = $url;
    }
    /**
     * @return the $editable
     */
    public function getEditable()
    {
        return $this->editable;
    }

 /**
     * @param field_type $editable
     */
    public function setEditable($editable)
    {
        $this->editable = $editable;
    }

    /**
     * @return the $type
     */
    public function getType()
    {
        return $this->type;
    }

 /**
     * @return the $selected
     */
    public function getSelected()
    {
        return $this->selected;
    }

 /**
     * @return the $num
     */
    public function getNum()
    {
        return $this->num;
    }

 /**
     * @param field_type $type
     */
    public function setType($type)
    {
        $this->type = $type;
    }

 /**
     * @param field_type $selected
     */
    public function setSelected($selected)
    {
        $this->selected = $selected;
    }

 /**
     * @param field_type $num
     */
    public function setNum($num)
    {
        $this->num = $num;
    }

}

?>