Efq Helper
==========

Entity field queries are a powerful tool for quering data from Backdrop CMS's
entity system. This module provides a EfqHelper class which extends the
EntityFieldQuery class providing shortcuts to common EFQ usage. This is a module
intended to assist in development and provides no functionality visible to an
end user.

Installation
------------

- Install this module using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules

- Add a dependency to efq_helper in your module's .info file.

- Initialize an EfqHelper object and perform queries (see Example Usage).

Example Usage
-------------

Here is an example to load the last 10 article type (bundle) nodes created with
field_featured (a checkbox, perhaps) set to 1.

```php
// Specify which entity type you're querying.
$query = new EfqHelper('node');

// Use standard EFQ methods to set the query.
$query->propertyCondition('status', 1)
  ->propertyCondition('type', 'article')
  ->fieldCondition('field_featured', 'value', 1)
  ->propertyOrderBy('created', 'DESC')
  ->range(0, 10);

// You can still get the raw EFQ data by calling the execute() method, this
// gives you "stub" entities.
$result = $query->execute();

// To get the fully-loaded nodes, simply call the result() method. Calling the
// execute() method before calling the result() method is optional.
$nodes = $query->result();

// To get the the fully-loaded node of the first result, call the first()
// method.
$node = $query->first();

// To get the the entity IDs from the result set, call the ids() method.
$nids = $query->ids();
```

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

Current Maintainers
-------------------

- Will Long (https://github.com/kerasai)

Credits
-------

This module was originally written for Drupal and ported to Backdrop by Will
Long (https://github.com/kerasai).
