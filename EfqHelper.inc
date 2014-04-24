<?php

/**
 * Description of EfqHelper
 */
class EfqHelper extends EntityFieldQuery {

  // Identifies the entity type this query is querying for.
  protected $entity_type;
  // Result of the underlying EntityFieldQuery, computed once then held onto
  // throughout the life the object.
  protected $raw = NULL;
  // Result of the underlying EntityFieldQuery, loaded into fully-populated 
  // entities. This is computed once then held onto throughout the life the
  // object.
  protected $result = NULL;
  // First result of the underlying EntityFieldQuery, loaded into a 
  // fully-populated entity. This is computed once then held onto throughout the 
  // life theobject.
  protected $first = NULL;

  public function __construct($entity_type) {
    $this->entity_type = $entity_type;
    $this->entityCondition('entity_type', $entity_type);
  }

  /**
   * Wrapper around EntityFieldQuery->execute().
   *
   * Ensures query is only ran once.
   */
  public function execute() {
    if ($this->raw === NULL) {
      $this->raw = parent::execute();
    }
    return $this->raw;
  }

  /**
   * Loads the full object data for entities returned by the EFQ.
   */
  public function result() {
    if ($this->result === NULL) {
      $raw = $this->execute();
      if (!empty($raw[$this->entity_type])) {
        $this->result = entity_load($this->entity_type, array_keys($raw[$this->entity_type]));
      }
      else {
        $this->result = array();
      }
    }
    return $this->result;
  }

  /**
   * Loads the full entity of the first result.
   */
  public function first() {
    if ($this->first === NULL) {
      $raw = $this->execute();
      if (!empty($raw[$this->entity_type])) {
        $etids = array_keys($raw[$this->entity_type]);
        $etid = reset($etids);
        $this->first = entity_load_single($this->entity_type, $etid);
      }
    }
    return $this->first;
  }

}
