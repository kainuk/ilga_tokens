<?php
/*
 * @author Klaas Eikelboom  <klaas.eikelboom@civicoop.org>
 * @date 18-Aug-2020
 * @license  AGPL-3.0
 */

class ilga_tokens_helper {

  /**
   * @var null
   */
  static $instance = null;

  /**
   * ilga_tokens_helper constructor.
   */
  public function __construct() {
  }

  /**
   * @return \ilga_tokens_helper|null
   */
  public static function instance(){
    if (!isset(self::$instance)){
      civicrm_initialize();
      self::$instance = new ilga_tokens_helper();
    }
    return self::$instance;
  }

  /**
   * @param $fieldId
   *
   * @return false|mixed
   */
  public function label($fieldId){
    try {
      $customField = $result = civicrm_api3('CustomField', 'getsingle', [
        'id' => $fieldId,
      ]);
      return "<i>{$customField['label']}</i>";
    } catch (CiviCRM_API3_Exception $ex){
      return false;
    }
  }

  /**
   * @param $fieldId
   * @param $entityId
   *
   * @return false|mixed
   */
  public function displayValue($fieldId,$entityId){
    try {
      $result = civicrm_api3('CustomValue', 'getdisplayvalue', [
        'entity_id' => $entityId,
        'custom_field_id' => $fieldId,
      ]);
      return $result['values'][$fieldId]['display'];
    } catch (CiviCRM_API3_Exception $ex){
      return false;
    }
  }

  /**
   * @param $fieldId
   * @param $entityId
   *
   * @return string
   */
  public function format($fieldId,$entityId){
    $fieldId = $this->validateFieldId($fieldId);
    if(!$fieldId){
      return "Unknown field $fieldId";
    }
    return $this->label($fieldId).' : '.$this->displayValue($fieldId,$entityId);
  }

  /**
   * @param $fieldId
   * @param $entityId
   *
   * @return string
   */
  public function formatText($fieldId,$entityId){
    $fieldId = $this->validateFieldId($fieldId);
    if(!$fieldId){
      return "Unknown field $fieldId";
    }
    return $this->label($fieldId).'<br/>'.'<p>'.$this->displayValue($fieldId,$entityId).'</p>';
  }

  private function validateFieldId($fieldId) {
    if(!is_numeric($fieldId)){
        return CRM_Core_DAO::singleValueQuery('select id from civicrm_custom_field where name=%1',[
            1=>[$fieldId,'String']
          ]
        );
    } else {
      return $fieldId;
    }
  }


}
